//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "RefPtr.h"
#import "ATInternet/ATInternet.h"
#import "ATInternet/ATTracker.h"

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

@property (nonatomic, strong) ATTracker* tracker;
@property ( nonatomic, retain ) UIWindow* window;
@property ( nonatomic, retain ) UIViewController* rootViewController;

@end
