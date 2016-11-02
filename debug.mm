//
//  Debug.m
//  Filtered debug output for objc/xcode
//
//  Created by Ketil Wright on 1/2/14.
//  Copyright (c) 2014 Ketil Wright. All rights reserved.
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

#include <debug.h>
#import <Foundation/Foundation.h>
#include <wchar.h>
uint32_t g_dbgFilter = dbg_error|dbg_warn | dbg_info;

void _DbgPrint(const wchar_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    NSUInteger len = wcslen(fmt) * sizeof(wchar_t);
    NSString *formatString = [[NSString alloc] initWithBytes:fmt length:len encoding:NSUTF32LittleEndianStringEncoding];
    NSString* formattedString = [[NSString alloc] initWithFormat:formatString arguments:args];
    NSLog(@"%@", formattedString);
    va_end(args);
}
