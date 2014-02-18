//
//  TLAppDelegate.h
//  TLStopwatch
//
//  Created by Carl on 29/07/13.
//  Copyright (c) 2013 Carl. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface TLStopwatch : NSObject
{
	NSTimeInterval baseElapsed;// added to current run
	NSDate* whenStarted;
}
@property NSTimeInterval elapsed;
@property (readonly) BOOL isRunning;

-(void)start;
-(void)stop;

@end





@interface TLAppDelegate : NSObject <NSApplicationDelegate>
{
	NSTimer* timer;
	TLStopwatch* stopwatch;
}

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *userEnteredTime;
@property (weak) IBOutlet NSTextField *currentTime;
- (IBAction)startStop:(id)sender;
@property (weak) IBOutlet NSButton *startStopButton;
- (IBAction)userSetTimeAction:(NSTextField *)sender;
@property (weak) IBOutlet NSProgressIndicator *progressIndicator;

@end
