//
//  MeasureFocus.cpp
//  PsPlugin
//
//  Created by Ketil Wright on 11/1/16.
//  Copyright © 2016 Ketil Wright. All rights reserved.
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


#include "MeasureFocus.h"
#include "matrix.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
MeasureFocus::MeasureFocus(long imgWidth, long row, long aperture, const uint16 *p)
    :
    m_bits(p),
    m_width(imgWidth),
    m_row(row),
    m_aperture(aperture),
    m_contrast(nullptr)
{
    m_contrast = new long[m_width];
    if(nullptr == m_contrast) throw "Out of memory";
    memset(m_contrast, 0, m_width * sizeof(int16));
}

MeasureFocus::~MeasureFocus()
{
    delete [] m_contrast;
}

void MeasureFocus::task()
{
    // valBasis is the center of a moving square of width
    // aperture * 2 + 1 pixels.
    const long nRowsOfInterest = m_aperture * 2 + 1;
    // loop across the entire m_row, with a sliding window & probe for
    // the maximum difference in color
    for(long column = m_aperture; column < m_width - m_aperture; ++column)
    {
        const long valBasis = m_bits[m_row * m_width + column];
        matrix<long> diffs(nRowsOfInterest, nRowsOfInterest);
        long yInx = 0;
        for(long y = -m_aperture; y < m_aperture; ++y)
        {
            long xInx = 0;
            for(long x = -m_aperture; x < m_aperture; ++x)
            {
                long diff = valBasis - m_bits[(m_row + x) * m_width + column + y];
                diffs(xInx++, yInx) = std::abs(diff);
            } //
            yInx++;
        }
        // dig up the maximum value
        m_contrast[column] = diffs.max();
    }
#if 0
    std::cout << "pixels:   ";
    for(size_t x = 0; x < m_width; ++x)
    {
        std::cout << std::hex << std::setw(4) << m_bits[m_row * m_width + x] << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "contrast: ";
    for(size_t x = 0; x < m_width; ++x)
    {
        std::cout << std::hex << std::setw(4) << m_contrast[x] << ", ";
    }
    std::cout << std::endl;
#endif
}
