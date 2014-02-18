
#import "MainMenuDelegate.h"
#import "StopwatchWindowDelegate.h"


/////////////////////////////////////////////////////////////////////////////
@implementation MainMenuDelegate

-(void)awakeFromNib
{
	//oc = [[NSObjectController alloc] init];
	activeStopwatches = [NSMutableArray new];
	
	[self addStopwatchWindow];
}

-(void)addStopwatchWindow
{
	StopwatchWindowDelegate *sw = [[StopwatchWindowDelegate alloc] initWithWindowNibName:@"StopwatchWindow"];
	
	NSLog(@"initWithWindowNibName returned %p", sw);

	sw.mainMenu = self;
	[sw showWindow:self];
	[activeStopwatches addObject:sw];

	[self dumpList];
}

-(void)dumpList
{
	NSLog(@"activeStopwatches:");
	NSLog(@"{");
	int i = 0;
	for(StopwatchWindowDelegate* sw in activeStopwatches)
	{
		NSLog(@"   %d: %p", i, sw);
		i ++;
	}
	NSLog(@"}");
}

-(void)removeStopwatchWindow:(id)window
{
	[window close];
	[activeStopwatches removeObject:window];

	NSLog(@"remove stopwatch %p (%lu left)", window, activeStopwatches.count);
	[self dumpList];

	if(activeStopwatches.count == 0)
	{
		NSLog(@"quitting...");
	 [[NSApplication sharedApplication] terminate:nil];
	}
}

- (IBAction)onQuit:(NSMenuItem *)sender
{
	// close all stopwatch windows.
	for(StopwatchWindowDelegate* sw in activeStopwatches)
	{
		[sw close];
	}
	[activeStopwatches removeAllObjects];
	
	[[NSApplication sharedApplication] terminate:nil];
}

- (IBAction)onNewStopwatchMenuClicked:(id)sender
{
	[self addStopwatchWindow];
}

@end






