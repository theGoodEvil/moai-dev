//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "RefPtr.h"
#if USE_DW_TRACKING
#import "ATInternet/ATInternet.h"
#import "ATInternet/ATTracker.h"
#endif
@class MoaiVC;
@class MoaiView;

//================================================================//
// MoaiAppDelegate
//================================================================//
@interface MoaiAppDelegate : NSObject < UIApplicationDelegate > {
@private

	MoaiView*	mMoaiView;
	UIWindow*	mWindow;	
	MoaiVC*		mMoaiVC;
}
#if USE_DW_TRACKING
@property (nonatomic, strong) ATTracker* tracker;
#endif
@property ( nonatomic, retain ) UIWindow* window;
@property ( nonatomic, retain ) UIViewController* rootViewController;

@end
