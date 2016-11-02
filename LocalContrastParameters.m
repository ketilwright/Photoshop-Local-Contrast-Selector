//
//  Parameters.m
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

#import "LocalContrastParameters.h"

@interface LocalContrastParameters ()
//

@end

@implementation LocalContrastParameters
- (id) initWithRadius:(long)radius withThreshold:(long)threshold withCores:(long)cores
{
    self = [super initWithWindowNibName:@"LocalContrastParameters"];
    if(self)
    {
        m_aperture = radius;
        m_threshold = threshold;
        m_cores = cores;
    }
    return self;
}
-(void)windowDidLoad
{
    [super windowDidLoad];
    [textAperture setStringValue:[NSString stringWithFormat:@"%ld", m_aperture]];
    [textThreshold setStringValue:[NSString stringWithFormat:@"%ld", m_threshold]];
    [textCores setStringValue:[NSString stringWithFormat:@"%ld", m_cores]];
}
-(void) windowWillLoad
{
    [super windowWillLoad];
}
- (int) showWindow
{
    [[self window] makeKeyAndOrderFront:self];
    NSInteger b = [NSApp runModalForWindow:[self window]];
    m_aperture = [textAperture integerValue];
    m_threshold = [textThreshold integerValue];
    m_cores = [textCores integerValue];
    [[self window] orderOut:self];
    return (int)b;
}

- (IBAction)didClickOK:(id)sender
{
    [NSApp endSheet:[self window]];
    [NSApp stopModalWithCode:NSModalResponseOK];
}

-(IBAction)didClickCancel:(id)sender
{
    [NSApp endSheet:[self window]];
    [NSApp stopModalWithCode:NSModalResponseCancel];
}
- (long) getAperture
{
    return m_aperture;
}
- (long) getThreshold
{
    return m_threshold;
}
-(long) getCores
{
    return m_cores;
}



@end
