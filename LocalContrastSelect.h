//
//  LocalContrastSelect.h
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
#include "ColorChannel.h"
class LocalContrastSelect
{
    PISelectionParams* m_params;
    ReadImageDocumentDesc *m_doc;
    int32 m_depth;
    VRect m_bounds;
    const long m_aperture;
    const long m_maxContrastThreshold;
    const long m_cores;
    ColorChannel *m_redChannel, *m_greenChannel, *m_blueChannel;
    bool probeColorChannels();
public:
    LocalContrastSelect(PISelectionParams *params, long aperture, long maxContrastThreshold, long cores);
    ~LocalContrastSelect();
};

