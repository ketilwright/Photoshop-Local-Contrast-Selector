//
//  Parameters.h
//  PsPlugin
//
//  Created by Ketil Wright on 3/10/16.
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

#import <Cocoa/Cocoa.h>

@interface LocalContrastParameters : NSWindowController
{
    IBOutlet NSTextField *textAperture;
    IBOutlet NSTextField *textThreshold;
    IBOutlet NSTextField *textCores;
    IBOutlet NSButton    *ckNormalize;
    IBOutlet NSButton    *bnOk;
    IBOutlet NSButton    *bnCancel;
    long m_aperture;
    long m_threshold;
    long m_cores;
    bool m_normalize;
}
- (id) initWithRadius:(long)radius withThreshold:(long)threshold withCores:(long)cores withNormalize:(bool)normal;
- (IBAction)didClickOK:(id)sender;
- (IBAction)didClickCancel:(id)sender;
- (int) showWindow;
- (long) getAperture;
- (long) getThreshold;
- (long) getCores;
- (bool) getNormalize;
@end
