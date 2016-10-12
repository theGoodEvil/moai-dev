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
    
    ATScreen *screen = [tracker.screens addWithName: @( msg ) ];
    screen.level2 = 34;

    [tracker.customVars addWithId:1 value:@"68" type:ATCustomVarTypeScreen]; 
    [tracker.customVars addWithId:2 value:@"34" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:3 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:4 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:5 value:@"" type:ATCustomVarTypeScreen]; // Page Name
    [tracker.customVars addWithId:6 value:@"1" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:7 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:8 value:@"" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:9 value:@"20150101" type:ATCustomVarTypeScreen];
    [tracker.customVars addWithId:10 value:@"" type:ATCustomVarTypeScreen]; // Chapter name

    if (tracker == nil) {
	    NSLog(@"%@", @"default Instance is null before dispatch" );
	    return;
    }

    [tracker dispatch];


}
