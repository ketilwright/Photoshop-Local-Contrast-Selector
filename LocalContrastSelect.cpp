//
//  LocalContrastSelect.cpp
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
#include "LocalContrastSelect.h"
#include "debug.h"
#include <algorithm>
#include "MeasureFocus.h"
LocalContrastSelect::LocalContrastSelect(PISelectionParams *_params, long _aperture, long _maxContrastThreshold, long _cores)
    :
    m_params(_params),
    m_aperture(_aperture),
    m_maxContrastThreshold(_maxContrastThreshold),
    m_cores(_cores),
    m_doc(_params->documentInfo),
    m_depth(_params->documentInfo->depth),
    m_bounds(_params->documentInfo->bounds),
    m_redChannel(nullptr), m_greenChannel(nullptr), m_blueChannel(nullptr)
{
    // pick up red, green and blue channels
    if(!probeColorChannels()) throw "color channels not supported";
    m_redChannel->probeContrast();
    m_greenChannel->probeContrast();
    m_blueChannel->probeContrast();
    // now collect max contrast per pixel & write
    // to m_params->newSelection
    PSChannelPortsSuite1 *suite = nullptr;
    if(noErr != m_params->sSPBasic->AcquireSuite(
                                  kPSChannelPortsSuite,
                                  kPSChannelPortsSuiteVersion3,
                                  (const void**)&suite))
    {
        throw "Couldn't acquire ports suite";
    }
    Boolean okSelection = false;
    if(noErr == suite->CanWrite(m_params->newSelection->port, &okSelection))
    {
        if(okSelection)
        {
            PixelMemoryDesc selDesc;
            VRect selBounds = m_bounds;
            int32 width = m_doc->bounds.right - m_doc->bounds.left;
            int32 height = m_doc->bounds.bottom - m_doc->bounds.top;
            // selection is 8bits (always?)
            selDesc.bitOffset = 0;
            selDesc.colBits = 8;
            selDesc.rowBits = width * 8;
            selDesc.depth = 8;
            selDesc.data = new int8[width * height];
            int8 *output = static_cast<int8*>(selDesc.data);
            long *redCtx = m_redChannel->m_contrast;
            long *greenCtx = m_greenChannel->m_contrast;
            long* blueCtx = m_blueChannel->m_contrast;
            int32 pos = 0;
            for(int32 row = 0; row < height; row++)
            {
                for(int32 col = 0; col < width; col++)
                {
                    int32 index = row * width + col;
                    int32 maxContrast = 0;
                    maxContrast = std::max<int16>(maxContrast, redCtx[index]);
                    maxContrast = std::max<int16>(maxContrast, greenCtx[index]);
                    maxContrast = std::max<int16>(maxContrast, blueCtx[index]);
                    if(maxContrast > m_maxContrastThreshold)
                        output[pos] = 0xff;
                    else
                        output[pos] = 0;
                    pos++;
                }
            }
            if(noErr != suite->WritePixelsToBaseLevel(m_params->newSelection->port, &selBounds, &selDesc))
            {
                DbgPrint(dbg_info, L"Failed to write selection\n");
            } else {
                DbgPrint(dbg_info, L"Successfully wrote selection\n");
            }
        }
    }
}
LocalContrastSelect::~LocalContrastSelect()
{
    delete m_redChannel;
    delete m_blueChannel;
    delete m_greenChannel;
}
// Function: probeColorChannels
// Parameters: none
// Remarks:
//      walks ReadImageDocument->targetCompositeChannels lookinf
//      for red/green/blue channel types.
// Returns:
//      true: if all rgb channels were found
//      false: one or more channels missing, or duplicate(s) found
bool LocalContrastSelect::probeColorChannels()
{
    bool ok = true;
    ReadChannelDesc *chan = m_doc->targetCompositeChannels;
    while(chan && ok)
    {
        switch (chan->channelType)
        {
            case ctRed:
            {
                if(nullptr == m_redChannel)
                {
                    m_redChannel = new ColorChannel(m_params, chan, m_aperture, m_cores);
                } else {
                    DbgPrint(dbg_error, L"Already found red channel\n");
                    ok = false;
                }
                break;
            }
            case ctGreen:
            {
                if(nullptr == m_greenChannel)
                {
                    m_greenChannel = new ColorChannel(m_params, chan, m_aperture, m_cores);
                } else {
                    DbgPrint(dbg_error, L"Already found green channel\n");
                    ok = false;
                }
                break;
            }
            case ctBlue:
            {
                if(nullptr == m_blueChannel)
                {
                    m_blueChannel = new ColorChannel(m_params, chan, m_aperture, m_cores);
                } else {
                    DbgPrint(dbg_error, L"Already found blue channel\n");
                    ok = false;
                }
                break;
            }
            default:
            {
                DbgPrint(dbg_error, L"Unsupported channel\n");
                ok = false;
                break;
            }
        }
        chan = chan->next;
    }
    return ok && (nullptr != m_redChannel) && (nullptr != m_greenChannel) && (nullptr != m_blueChannel);
}
