//
//  class MeasureFocus.h
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
#include "job.hpp"
#include <PITypes.h>
class MeasureFocus : public job
{
   // pointer to the image data. Only 16bit format
   // is supported.
   const uint16 *m_bits;
   // memory format
   // PS gives us image width in bits, I want it
   // in pixels
   const long m_width;
   // Row within image bits upon which we operate
   const long m_row;
   // the distance from the pixel of interest to
   // the edges of a moving window, within which
   // we probe for contrast.
   const long m_aperture;
   // the output of this job lands here
   uint16 *m_contrast;
public:
    MeasureFocus(long imgWidth, long row, long aperture, const uint16 *p);
    ~MeasureFocus();
    void task();
    const uint16 * contrast() const { return m_contrast; }
};