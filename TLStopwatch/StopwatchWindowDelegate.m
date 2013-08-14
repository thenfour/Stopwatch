
#import "StopwatchWindowDelegate.h"
#import "MainMenuDelegate.h"

@implementation StopwatchWindowDelegate

-(void)handleTimer:(NSTimer*)timer
{
	NSString* sHours;
	NSString* sMinutes;
	NSString* sSeconds;
	NSString* sFraction;
	
	[TLStopwatch timeIntervalToString:stopwatch.elapsed hours:&sHours minutes:&sMinutes seconds:&sSeconds fraction:&sFraction];
		
	NSString* html = [NSString stringWithFormat:
										@"<div style=\"text-align:center;font-family:Helvetica;font-weight:bold;font-size:36px;color:#%@;letter-spacing:2px;\">"
										@"<span style=\"\">%@</span>"// hours
										@"<span style=\"font-size:20px;color:#aaa;\">h</span>"
										@"<span style=\"\">%@</span>"// minutes
										@"<span style=\"font-size:20px;color:#aaa;\">m</span>"
										@"<span style=\"\">%@</span>"// seconds
										@"<span style=\"font-size:20px;color:#aaa;\">s</span>"
										@"<span style=\"font-size:28px;color:#888;\">%@</span>"// fraction
										@"</div>"
										,
										stopwatch.isRunning ? @"2b2" : @"bcd",
										sHours,
										sMinutes,
										sSeconds,
										sFraction];
	[_currentTime setAttributedStringValue:[[NSAttributedString alloc] initWithHTML:[html dataUsingEncoding:NSUnicodeStringEncoding] documentAttributes:nil]];
	
	_progress.maxValue = [TLStopwatch stringToTimeInterval:_txtDestTime.stringValue];
	_progress.doubleValue = stopwatch.elapsed;
}

-(void)windowDidLoad
{
	[super windowDidLoad];

	isClosing = FALSE;
	
	NSLog(@"windowDidLoad on child nib; self = %p", self);
	stopwatch = [TLStopwatch new];
	[stopwatch start];

//	[_progressIndicator setHidden:TRUE];
	
	[_randomText setFont:[NSFont fontWithName:@"Futura" size:19]];

	[self updateState];
	
	timer = [NSTimer scheduledTimerWithTimeInterval: 0.12
																					 target: self
																				 selector: @selector(handleTimer:)
																				 userInfo: nil
																					repeats: YES];
}

-(void)updateState
{
	[_startStopButton setTitle:(stopwatch.isRunning ? @"Pause" : @"Go")];
	/*
	if(stopwatch.isRunning)
		[_progressIndicator startAnimation:self];
	else
		[_progressIndicator stopAnimation:self];
	*/
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

- (IBAction)resetWasClicked:(id)sender
{
	stopwatch.elapsed = 0;
}

@end
