// ADOBE SYSTEMS INCORPORATED
// Copyright  1993 - 2002 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------
//-------------------------------------------------------------------------------
//
//	File:
//		Selectorama.r
//
//	Description:
//		This file contains the resource text descriptions for the
//		for the Selection module Selectorama, an example module
//		that just returns a pixel selection.
//
//	Use:
//		Use selection modules to return pixel or path selections on a new
//		layer or the current layer.
//
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//	Definitions -- Required by include files.
//-------------------------------------------------------------------------------

// The About box and resources are created in PIUtilities.r.
// You can easily override them, if you like.
// plugInName defines the string which appears in the cs6 select menu
#define plugInName			"Local Contrast Selector"
#define plugInCopyrightYear	"1996"
#define plugInDescription \
"An plug-in local contrast selection module for Adobe Photoshop®."

//-------------------------------------------------------------------------------
//	Definitions -- Required by other resources in this rez file.
//-------------------------------------------------------------------------------

// Dictionary (aete) resources:

#define vendorName			"Ketil Wright"
#define plugInAETEComment \
"local contrast selector plug-in"

#define plugInSuiteID		'sdk7'
#define plugInClassID		plugInSuiteID
#define plugInEventID		'selM'

//-------------------------------------------------------------------------------
//	Set up included files for Macintosh and Windows.
//-------------------------------------------------------------------------------

#include "PIDefines.h"

#ifdef __PIMac__
#include "PIGeneral.r"
#include "PIUtilities.r"
#elif defined(__PIWin__)
#define Rez
#include "PIGeneral.h"
#include "PIUtilities.r"
#endif

#include "PITerminology.h"
#include "PIActions.h"

//#include "PsPluginTerminology.h"	// Terminology for plug-in.

//-------------------------------------------------------------------------------
//	PiPL resource
//-------------------------------------------------------------------------------

resource 'PiPL' (ResourceID, plugInName " PiPL", purgeable)
{
    {
        Kind { Selection },
        Name { plugInName "..." },
        Category { vendorName },
        Version { (latestSelectionVersion << 16) | latestSelectionSubVersion },
        
        HasTerminology { plugInClassID, plugInEventID, ResourceID, vendorName " " plugInName },
        /* classID, eventID, aete ID, uniqueString */
        
        EnableInfo { "true" },
        
        #ifdef __PIMac__
        #if (defined(__i386__))
        
        CodeMacIntel32 { "PluginMain" },
        
        /* If your plugin uses Objective-C, Cocoa, for UI it should not be
         unloaded, this flag is valid for 32 bit plug-ins only and
         should not be used in any windows section */
        
        // off for now as this plug-in has no Objective-C Cocoa {},
        
        #endif
        #if (defined(__x86_64__))
        CodeMacIntel64 { "PluginMain" },
        #endif
        #else
        #if defined(_WIN64)
        CodeWin64X86 { "PluginMain" },
        #else
        CodeWin32X86 { "PluginMain" },
        #endif
        #endif
        
    }
};

//-------------------------------------------------------------------------------
//	Dictionary (scripting) resource
//-------------------------------------------------------------------------------
// end Selectorama.r
