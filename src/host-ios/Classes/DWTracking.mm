#include "DWTracking.h"
#import <moai-sim/host.h>
#import "ATInternet/ATInternet.h"
#import "ATInternet/ATTracker.h"
#import "ATInternet/ATScreen.h"
#import "ATInternet/ATCustomVar.h"



bool isTrackerInitalized = false;



void dwTrackingLogProgress( cc8* msg ) {

    if (! isTrackerInitalized ) return;
    ATTracker* tracker = [[ATInternet sharedInstance] defaultTracker];
    
    NSString* path = [NSString stringWithUTF8String:msg];
    NSLog( @"msg is %@ path is %@", @(msg), path);
    NSRange pageSeperatorRange = [path rangeOfString: @"::" options: NSBackwardsSearch ];
    
    NSString* page = [path substringToIndex: pageSeperatorRange.location ];
    
    NSString* chapter = [path substringFromIndex: (pageSeperatorRange.location + pageSeperatorRange.length)];
    
    NSLog( @"Page is %@ chapter is %@", page, chapter );
    
    ATScreen *screen = [tracker.screens addWithName: @( msg ) ];
    screen.level2 = 34;

    [tracker.customVars addWithId:1 value:@"68" type:ATCustomVarTypeScreen]; 
    [tracker.customVars addWithId:2 value:@"34" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:3 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:4 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:5 value:chapter type:ATCustomVarTypeScreen]; 
    [tracker.customVars addWithId:6 value:@"1" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:7 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:8 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:9 value:@"20150101" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:10 value:page type:ATCustomVarTypeScreen];

    [tracker.customVars addWithId:1 value:@"68" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:2 value:@"34" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:3 value:@"" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:4 value:@"" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:5 value:chapter type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:6 value:@"1" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:7 value:@"" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:8 value:@"" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:9 value:@"20150101" type:ATCustomVarTypeApp];
    [tracker.customVars addWithId:10 value:page type:ATCustomVarTypeApp]; 
    
    if (tracker == nil) {
	    NSLog(@"%@", @"default Instance is null before dispatch" );
	    return;
    }

    [screen sendView];


}
