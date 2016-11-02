//
//  ColorChannel.cpp
//  PsPlugin
//
//  Created by Ketil Wright on 3/9/16.
//  Copyright (c) 2016 Ketil Wright. All rights reserved.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "ColorChannel.h"
#include <list>
#include "debug.h"
#include "MeasureFocus.h"

// TODO: refactor somehere more visible.
bool operator == (VRect const& lhs, VRect const& rhs)
{
    return lhs.left == rhs.left &&
           lhs.right == rhs.right &&
           lhs.top == rhs.top &&
           lhs.bottom == rhs.bottom;
}
bool operator != (VRect const& lhs, VRect const& rhs)
{
    return !(lhs == rhs);
}
ColorChannel::ColorChannel(PISelectionParams *selectionParams, ReadChannelDesc *channelDesc, long _aperture, long _cores)
    :
    m_selectionParams(selectionParams),
    m_channelDesc(channelDesc),
    m_doc(selectionParams->documentInfo),
    m_suite(nullptr),
    //m_port(port),
    m_bits8(nullptr),
    m_bits16(nullptr),
    m_bits32(nullptr),
    m_contrast(nullptr),
    m_aperture(_aperture),
    m_cores(_cores)

{
    // keep the channel ports suite available for the entire time this object is acquired
    if(noErr != m_selectionParams->sSPBasic->AcquireSuite(
            kPSChannelPortsSuite,
            kPSChannelPortsSuiteVersion3,
            (const void**)&m_suite))
    {
        throw "Couldn't acquire ports suite";
    }
    // avoid constant groveling in ReadImageDocumentDesc
    m_width = m_doc->bounds.right - m_doc->bounds.left;
    m_height = m_doc->bounds.bottom - m_doc->bounds.top;
    m_desc.bitOffset = 0;
    m_desc.depth = m_doc->depth;
    m_desc.rowBits = m_width * m_doc->depth;
    m_desc.colBits = m_doc->depth;
    m_desc.data = nullptr;
    switch(m_doc->depth)
    {
        // todo: support more image depths
        case 8:
        {
            throw "unsupported bit depth";
            //m_bits8 = new uint8[m_width * m_height];
            //m_desc.data = m_bits8;
            //break;
        }
        case 16:
        {
            m_bits16 = new uint16[m_width * m_height];
            m_desc.data = m_bits16;
            break;
        }
        case 32:
        {
            throw "unsupported bit depth";
            //m_bits32 = new uint32[m_width * m_height];
            //m_desc.data = m_bits32;
            //break;
        }
        default:
        {
            throw "unsupported bit depth";
        }
    }
    if(nullptr == m_desc.data) throw "Failed allocation for pixel data";
    // read the pixel data for this color channel
    VRect wrote = m_doc->bounds;
    
    if(noErr != m_suite->ReadPixelsFromLevel(m_channelDesc->port, 0 /*level*/, &wrote, &m_desc))
    {
        throw "Failed to read pixels";
    }
    if(wrote != m_doc->bounds)
    {
        throw "bounds mismatch in pixel read operation";
    }
    m_contrast = new long[m_width * m_height];
    memset(m_contrast, 0, m_width * m_height * sizeof(m_contrast[0]));
    
    
}
ColorChannel::~ColorChannel()
{
    // release the ports suite.
    m_selectionParams->sSPBasic->ReleaseSuite(kPSChannelPortsSuite, kPSChannelPortsSuiteVersion3);
    switch(m_doc->depth)
    {
        case 8:
        {
            delete[] m_bits8;
            break;
        }
        case 16:
        {
            delete [] m_bits16;
            break;
        }
        case 32:
        {
            delete [] m_bits32;
            break;
        }
        default:
        {
            throw "unsupported bit depth";
        }
    }
    delete [] m_contrast;
}
void ColorChannel::probeContrast()
{
    const unsigned int maxProcs = (-1 == m_cores) ? std::thread::hardware_concurrency() : (unsigned int)m_cores;
    // TODO: aperture is incorrect int type. s
    long rowIndex = m_aperture;
    long outputIndex = m_aperture;
    // keep all processors busy
    while(rowIndex < m_height - m_aperture)
    {
        std::list<MeasureFocus*> jobs;
        for(int proc = 0; (proc < maxProcs) && (rowIndex < m_height - m_aperture); ++proc)
        {
            jobs.push_back(new MeasureFocus(m_width, rowIndex++, m_aperture, m_bits16));
        }
        // launch all measure focus jobs & wait for completion.
        for(auto job = jobs.begin(); job != jobs.end(); ++job) (*job)->spawn();
        for(auto job = jobs.begin(); job != jobs.end(); ++job) (*job)->join();
        // collect the output
        for(auto job = jobs.begin(); job != jobs.end(); ++job)
        {
            memcpy(m_contrast + outputIndex * m_width, (*job)->contrast(), m_width * sizeof(m_contrast[0]));
            outputIndex++;
        }
        // cleanup & run the next batch
        while(!jobs.empty())
        {
            delete jobs.front();
            jobs.pop_front();
        }
    }
}
