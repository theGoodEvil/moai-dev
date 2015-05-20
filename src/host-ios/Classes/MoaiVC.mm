//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-core/headers.h>
#import <moai-sim/host.h>
#import "MoaiVC.h"
#import "MoaiView.h"

//================================================================//
// MoaiVC ()
//================================================================//
@interface MoaiVC ()

	//----------------------------------------------------------------//	
	-( void ) updateOrientation :( UIInterfaceOrientation )orientation;

@end

//================================================================//
// MoaiVC
//================================================================//
@implementation MoaiVC

	//----------------------------------------------------------------//
	-( void ) willRotateToInterfaceOrientation :( UIInterfaceOrientation )toInterfaceOrientation duration:( NSTimeInterval )duration {
		
        // do not update interface orientation here, this will break the view
		// [ self updateOrientation:toInterfaceOrientation ];
	}

	//----------------------------------------------------------------//
	- ( id ) init {
	
		self = [ super init ];
		if ( self ) {
		
		}
		return self;
	}

	//----------------------------------------------------------------//
	// this function is deprecated as for iOS 6.0
	- ( BOOL ) shouldAutorotateToInterfaceOrientation :( UIInterfaceOrientation )interfaceOrientation {
		
        /*
            The following block of code is used to lock the sample into a Landscape orientation, skipping the Portrait views as you rotate your device.
            To complete this feature, you must specify the correct Landscape as the only supported orientations in your plist under the setting,
                "Supported Device Orientations"
            Also, don't forget to the correct initial bounds in MoaAppDelegate.mm
         */
        
        if (( interfaceOrientation == UIInterfaceOrientationLandscapeLeft ) || ( interfaceOrientation == UIInterfaceOrientationLandscapeRight )) {
            return true;
        }
        
        return false;
        
        /*
            The following is used to support all view orientations.
         */
        
        //return true;
	}

	// this function is how the supported interace orientations are managed in iOS 6.0 or later
	- ( NSUInteger ) supportedInterfaceOrientations {
		return UIInterfaceOrientationMaskLandscape;
	}

    // supportedInterfaceOrientations only gets called when this method returns true
	- ( BOOL ) shouldAutorotate {
		return true;
	}

    // replacement function for deprecated willRotateToInterfaceRotation
	- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
        // we have to update the interface orientation here, or it will break.
        // this is strange though, probably apple switched height and width back again
        [ self updateOrientation:UIInterfaceOrientationLandscapeLeft ];
    }

	//----------------------------------------------------------------//
	-( void ) updateOrientation :( UIInterfaceOrientation )orientation {

		MoaiView* view = ( MoaiView* )self.view;        
		
		if (( orientation == UIInterfaceOrientationPortrait ) || ( orientation == UIInterfaceOrientationPortraitUpsideDown )) {
			NSLog(@"Update orientation portrait");		
            
            if ([ view akuInitialized ] != 0 ) {
                AKUSetOrientation ( AKU_ORIENTATION_PORTRAIT );
                AKUSetViewSize (( int )view.width, ( int )view.height );
            }
		}
		else if (( orientation == UIInterfaceOrientationLandscapeLeft ) || ( orientation == UIInterfaceOrientationLandscapeRight )) {
			NSLog(@"Update orientation landscape");

            if ([ view akuInitialized ] != 0 ) {
                AKUSetOrientation ( AKU_ORIENTATION_LANDSCAPE );
                AKUSetViewSize (( int )view.height, ( int )view.width);
            }
		}
	}
	
@end