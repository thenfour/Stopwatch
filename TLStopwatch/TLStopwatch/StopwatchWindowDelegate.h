//
//  StopwatchWindowDelegate.h
//  TLStopwatch
//
//  Created by Carl on 12/08/13.
//  Copyright (c) 2013 Carl. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Utility.h"

@protocol MainMenuInfo;

@interface StopwatchWindowDelegate : NSWindowController
{
	NSTimer* timer;
	TLStopwatch* stopwatch;
	BOOL isClosing;
}

@property (assign) IBOutlet id<MainMenuInfo> mainMenu;
@property (unsafe_unretained) IBOutlet NSTextView *randomText;

@property (weak) IBOutlet NSTextField *userEnteredTime;
@property (weak) IBOutlet NSTextField *currentTime;
@property (weak) IBOutlet NSButton *startStopButton;
//@property (weak) IBOutlet NSProgressIndicator *progressIndicator;
@property (weak) IBOutlet NSTextField *txtDestTime;
@property (weak) IBOutlet NSProgressIndicator *progress;

- (IBAction)onMinus:(NSButton *)sender;
- (IBAction)onPlus:(NSButton *)sender;
- (IBAction)onPlusMInus:(NSSegmentedCell *)sender;

- (IBAction)startStop:(id)sender;
- (IBAction)userSetTimeAction:(NSTextField *)sender;
- (IBAction)resetWasClicked:(id)sender;

-(void)windowDidLoad;


@end
