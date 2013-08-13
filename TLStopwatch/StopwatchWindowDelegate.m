
#import "StopwatchWindowDelegate.h"
#import "MainMenuDelegate.h"

@implementation StopwatchWindowDelegate

-(void)handleTimer:(NSTimer*)timer
{
	_currentTime.stringValue = [TLStopwatch timeIntervalToString:stopwatch.elapsed];
}

-(void)windowDidLoad
{
	[super windowDidLoad];

	isClosing = FALSE;
	
	NSLog(@"windowDidLoad on child nib; self = %p", self);
	stopwatch = [TLStopwatch new];
	[stopwatch start];
	[self updateState];
	_progressIndicator.controlTint = NSGraphiteControlTint;

}

-(void)updateState
{
	[_startStopButton setTitle:(stopwatch.isRunning ? @"Stop" : @"Start")];
	_currentTime.stringValue = [TLStopwatch timeIntervalToString:stopwatch.elapsed];
	timer = [NSTimer scheduledTimerWithTimeInterval: 0.08
																					 target: self
																				 selector: @selector(handleTimer:)
																				 userInfo: nil
																					repeats: YES];
	
	if(stopwatch.isRunning)
		[_progressIndicator startAnimation:self];
	else
		[_progressIndicator stopAnimation:self];
}

-(void)windowWillClose:(id)sender
{
	if(isClosing)
		return;
	
	isClosing = TRUE;
	NSLog(@"windowWillClose; self = %p", self);
	[self.mainMenu removeStopwatchWindow:self];
}

- (IBAction)onMinus:(NSButton *)sender
{
	NSLog(@"onMinus on child nib; self = %p", self);
	[self close];
}

- (IBAction)onPlus:(NSButton *)sender
{
	NSLog(@"onPlus on child nib; self = %p", self);
	[self.mainMenu addStopwatchWindow];
}

- (IBAction)onPlusMInus:(NSSegmentedCell *)sender {
	if(sender.selectedSegment == 0)
	{
		NSLog(@"onPlus on child nib; self = %p", self);
		[self.mainMenu addStopwatchWindow];
	}
	else if(sender.selectedSegment == 1)
	{
		NSLog(@"onMinus on child nib; self = %p", self);
		[self close];
	}
[sender setSelectedSegment:-1];
}

- (IBAction)startStop:(id)sender {
	if(stopwatch.isRunning)
		[stopwatch stop];
	else
		[stopwatch start];
	[self updateState];
}

- (IBAction)userSetTimeAction:(NSTextField *)sender {
	stopwatch.elapsed = [TLStopwatch stringToTimeInterval:_userEnteredTime.stringValue];
	[self updateState];
}

@end
