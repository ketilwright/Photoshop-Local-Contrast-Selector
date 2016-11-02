//
//  debug.h
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
#include <stdint.h>
enum DbgFilter : uint32_t
{
    dbg_error       = 0x00000001,
    dbg_warn        = 0x00000002,
    dbg_print       = 0x00000004,
    dbg_info        = 0x00000008,
    dbg_reserved    = 0x80000000,
    dbg_all         = 0xffffffff
};
#define DEBUGLOG 1
#if defined (DEBUGLOG)
extern uint32_t g_dbgFilter;
void _DbgPrint(const wchar_t *fmt,...);
#define DbgPrint(filter, fmt, ...) if(g_dbgFilter & (filter)) { _DbgPrint(fmt, ##__VA_ARGS__) ;}
#else
#define DbgPrint(filter, args) 
#endif
