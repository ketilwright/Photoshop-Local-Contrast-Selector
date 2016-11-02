//
//  matrix.hpp
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
#include <vector>
#include <iostream>
#include <iomanip>
template<typename elemType=double>
class matrix
{
    typedef std::vector<elemType> colType;
    typedef std::vector<colType>  rowType;
    rowType m_rows;
public:
    matrix(size_t rows, size_t cols)
    {
        const elemType val(0);
        m_rows.reserve(rows);
        for(size_t y = 0; y < rows; y++)
        {
            m_rows.push_back(colType());
            auto &row = *m_rows.rbegin();
            row.reserve(cols);
            for(size_t x = 0; x < cols; x++)
            {
                row.push_back(val);
            }
        }
    }
    ~matrix()
    {
    }
    elemType max() const
    {
        elemType max(0);
        size_t nRows = m_rows.size();
        size_t nCols = m_rows[0].size();
        for(size_t r = 0; r < nRows; ++r)
            for(size_t c = 0; c < nCols; ++c)
                max = std::max<elemType>(max, m_rows[r][c]);
        return max;
    }
    size_t rows() const { return m_rows.size(); }
    size_t cols() const { return m_rows[0].size();}
    elemType & at(size_t row, size_t col)
    {
        return m_rows[row][col];
    }
    elemType& operator() (size_t row, size_t col)
    {
        return m_rows[row][col];
    }
    void print(std::ostream &os)
    {
        for (unsigned r = 0; r < rows(); ++r)
        {
            os << "{";
            for (unsigned c = 0; c < cols(); ++c)
            {
                os << std::setprecision(3) << std::setw(3) << std::fixed << std::right << at(r, c) << ", ";
            }
            os << "}" << std::endl;
        }
    }
};
