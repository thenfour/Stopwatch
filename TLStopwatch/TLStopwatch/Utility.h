//
//  TLStopwatchUtility.h
//  TLStopwatch
//
//  Created by Carl on 12/08/13.
//  Copyright (c) 2013 Carl. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TLStopwatch : NSObject
{
	NSTimeInterval baseElapsed;// added to current run
	NSDate* whenStarted;
}


+(NSString*)timeIntervalToString:(NSTimeInterval)i;
+(void)timeIntervalToString:(NSTimeInterval)i hours:(NSString**)hours minutes:(NSString**)minutes seconds:(NSString**)seconds fraction:(NSString**)fraction;
+(NSTimeInterval)stringToTimeInterval:(NSString*)__inp;
+(NSDate*)UTCDate;

@property NSTimeInterval elapsed;
@property (readonly) BOOL isRunning;

-(void)start;
-(void)stop;

@end


