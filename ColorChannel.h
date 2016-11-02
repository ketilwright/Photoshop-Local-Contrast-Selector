//
//  ColorChannel.h
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

#pragma once
#include <PITypes.h>
#include <PISelection.h>
#include <PIChannelPortsSuite.h>
class ColorChannel
{
    PISelectionParams *m_selectionParams;
    ReadImageDocumentDesc *m_doc;
    ReadChannelDesc *m_channelDesc;
    // interface used for reading pixel data
    PSChannelPortsSuite1 *m_suite;
    // information about the pixels on a color channel
    PixelMemoryDesc m_desc;
    uint8  *m_bits8; // not implemented
    uint16 *m_bits16;
    uint32 *m_bits32;// not implemented
    // avoid constant groveling in ReadImageDocumentDesc
    // for image dimensions
    int32 m_width, m_height;
    const long m_aperture;
    const long m_cores;

public:
    ColorChannel(PISelectionParams *selectionParams, ReadChannelDesc *channelDesc, long aperture, long cores);
    ~ColorChannel();
    void probeContrast();
    // array containing local contrast
    // TODO: should be private
    long *m_contrast;
    const uint16 *bits16() const { return m_bits16; }
};