//
//  TLAppDelegate.m
//  TLStopwatch
//
//  Created by Carl on 29/07/13.
//  Copyright (c) 2013 Carl. All rights reserved.
//

#import "TLAppDelegate.h"

@implementation TLStopwatch : NSObject

+(NSString*)timeIntervalToString:(NSTimeInterval)i
{
	//i = i / 4;
	// hh:mm:ss
	int hours = (int)(i / 3600);
	int minutes = (int)((i - (hours * 3600)) / 60);
	int seconds = (int)(i - (hours * 3600) - (minutes * 60));
	int fraction = ((i - floor(i)) * 10);
	
	return [NSString stringWithFormat:@"%02d:%02d.%02d.%02d", hours, minutes, seconds, fraction];
}

+(NSTimeInterval)stringToTimeInterval:(NSString*)__inp
{
	NSString* inp = [__inp copy];
	// H:M.s
	// M.s
	// H:
	// s
	// M.
	int h = 0;
	int m = 0;
	int s = 0;
	
	// look for hours (before colon)
	NSRange colon = [inp rangeOfString:@":"];
	if(colon.location != NSNotFound)
	{
		h = [[inp substringWithRange:NSMakeRange(0,colon.location)] intValue];
		inp = [inp substringFromIndex:colon.location + 1];
	}
	
	// look for minutes (before period)
	NSRange period = [inp rangeOfString:@"."];
	if(period.location != NSNotFound)
	{
		m = [[inp substringWithRange:NSMakeRange(0,period.location)] intValue];
		inp = [inp substringFromIndex:period.location + 1];
	}
	
	// if there's anything leftover... seconds.
	s = [inp intValue];
	
	return s + (m * 60) + (h * 3600);
}

+(NSDate*)UTCDate
{
	NSDate *localDate = [NSDate date];// get the date
	NSTimeInterval timeZoneOffset = [[NSTimeZone defaultTimeZone] secondsFromGMT]; // You could also use the systemTimeZone method
	NSTimeInterval gmtTimeInterval = [localDate timeIntervalSinceReferenceDate] - timeZoneOffset;
	NSDate *gmtDate = [NSDate dateWithTimeIntervalSinceReferenceDate:gmtTimeInterval];
	return gmtDate;
}

-(id)init
{
	self = [super init];
	if(self)
	{
		_isRunning = FALSE;
		baseElapsed = 0;
	}
	return self;
}

-(void)start{
	if(_isRunning)
		return;
	_isRunning = TRUE;
	whenStarted = [TLStopwatch UTCDate];
}
-(void)stop{
	if(!_isRunning)
		return;
	baseElapsed = [self elapsed];
	_isRunning = FALSE;
}

-(NSTimeInterval)elapsed
{
	if(!_isRunning)
		return baseElapsed;
	
	return baseElapsed - [whenStarted timeIntervalSinceDate:[TLStopwatch UTCDate]];
}

-(void)setElapsed:(NSTimeInterval)elapsed
{
	BOOL wasRunning = _isRunning;
	[self stop];
	baseElapsed = elapsed;
	if(wasRunning)
		[self start];
}

@end

/////////////////////////////////////////////////////////////////////////////
@implementation TLAppDelegate

-(void)handleTimer:(NSTimer*)timer
{
	_currentTime.stringValue = [TLStopwatch timeIntervalToString:stopwatch.elapsed];
}

-(void)awakeFromNib
{
	stopwatch = [TLStopwatch new];
	[stopwatch start];
	//[_window setDefaultButtonCell:_startStopButton.cell];
	[self updateState];
	_progressIndicator.controlTint = NSGraphiteControlTint;
}

-(void)updateState
{
	[_startStopButton setTitle:(stopwatch.isRunning ? @"Stop" : @"Start")];
	_currentTime.stringValue = [TLStopwatch timeIntervalToString:stopwatch.elapsed];
	timer = [NSTimer scheduledTimerWithTimeInterval: .1
																					 target: self
																				 selector: @selector(handleTimer:)
																				 userInfo: nil
																					repeats: YES];
	
	if(stopwatch.isRunning)
		[_progressIndicator startAnimation:self];
	else
		[_progressIndicator stopAnimation:self];
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
