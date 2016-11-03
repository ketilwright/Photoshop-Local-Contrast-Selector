//
//  main.cpp
//  PsPlugin
//
//  Created by Ketil Wright on 2/10/16.
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

// Includes here depend on $PHOTOSHOPSDK environment variable and include path
#include <PIDefines.h>
#include <PITypes.h>
#include <PSIntTypes.h>
#include <PISelection.h>
#include <PIChannelPortsSuite.h>

#include <chrono>
#include <iostream>
#include "debug.h"
#include "LocalContrastSelect.h"
#include "LocalContrastParameters.h"


int16 Execute(PISelectionParams *selectionParamBlock)
{
    long aperture = 1;
    long maxContrastThreshold = 1000;
    long cores = -1;
    bool normalize = true;
    LocalContrastParameters *params = [[LocalContrastParameters alloc]
                                       initWithRadius:aperture
                                        withThreshold:maxContrastThreshold
                                            withCores:cores
                                        withNormalize:normalize];
    [[params window] center];
    
    if(NSModalResponseOK == [params showWindow ])
    {
        aperture = [params getAperture];
        maxContrastThreshold = [params getThreshold];
        cores = [params getCores];
        normalize = [params getNormalize];
        auto startTime = std::chrono::system_clock::now();
        LocalContrastSelect *lcs = new LocalContrastSelect(selectionParamBlock, aperture, maxContrastThreshold, cores, normalize);
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        std::cout << "aperture: " << aperture << " cores: " << cores << " time: " << duration.count() << std::endl;
        DbgPrint(dbg_info, L"duration: %f", duration.count());
        delete lcs;
    }
    return 0;

}


DLLExport MACPASCAL void PluginMain (const int16 selector,
                                     PISelectionParams *selectionParamBlock,
                                     intptr_t *data, // PS maintains for the plugin across invocations. Will be 0 the first time
                                     int16 *result)
{
    try {
        switch(selector)
        {
            case selectionSelectorAbout:
            {
                // TODO: implement about box
                DbgPrint(dbg_info, L"PluginMain selectionSelectorAbout");
                break;
            }
            case selectionSelectorExecute:
            {
                DbgPrint(dbg_info, L"PluginMain selectionSelectorExecute");
                *result = Execute(selectionParamBlock);
                break;
            }
            default:
            {
                DbgPrint(dbg_info, L"PluginMain unsupported selector: 0x%x", selector);
                break;
            }
        }
    } catch(...)
    {
        if(NULL != result)
        {
            *result = -1;
        }
    }
    
}
