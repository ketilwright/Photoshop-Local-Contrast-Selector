//
//  job.hpp
//
//
//  Created by Ketil Wright on 11/1/16.
//  Copyright © 2016 Ketil Wright. All rights reserved.
//
//  A minimal base class for multithreaded execution of jobs
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
#include <thread>
class job
{
    std::thread *m_worker;
public:
    job() : m_worker(nullptr){}
    virtual ~job() { delete m_worker; }
    // spawn the thread, which invokes task
    void spawn()
    {
        m_worker = new std::thread([this] { this->task(); } );
    }
    // wait for completion.
    void join()
    {
        if(m_worker && m_worker->joinable())
        {
            m_worker->join();
        }
    }
    // derived classes implement this to do their work
    virtual void task() = 0;
};