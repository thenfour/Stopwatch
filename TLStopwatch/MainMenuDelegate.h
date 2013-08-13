//
//  TLAppDelegate.h
//  TLStopwatch
//
//  Created by Carl on 29/07/13.
//  Copyright (c) 2013 Carl. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Utility.h"


@protocol MainMenuInfo
-(void)removeStopwatchWindow:(id)window;
-(void)addStopwatchWindow;
@end

@interface MainMenuDelegate : NSViewController <MainMenuInfo>
{
	NSMutableArray *activeStopwatches;
}

-(void)addStopwatchWindow;
-(void)removeStopwatchWindow:(id)window;

-(void)awakeFromNib;

- (IBAction)onQuit:(NSMenuItem *)sender;
- (IBAction)onNewStopwatchMenuClicked:(id)sender;

@end
