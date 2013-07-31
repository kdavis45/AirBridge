//
//  ImpActivityAgent.m
//  Impressol Utility
//
//  Created by Development Team on 1/12/10.
//  Copyright 2010 Impressol. All rights reserved.
//

#import "ImpActivityAgent.h"
#import <QuartzCore/QuartzCore.h>

static ImpActivityAgent* agent;

@implementation ImpActivityAgent
- (id)init{
	return nil;
}

- (id)myinit
{
	if( (self = [super init]))
    {
		busyCount = 0;
        view= [[UIView alloc] initWithFrame:CGRectMake(0,0,320,480)];

        [view.layer setCornerRadius:10.0f];
		view.backgroundColor = [UIColor clearColor]; 
        
        UIView *mView = [[UIView alloc] init];
        
        if(IS_IPHONE5)
        {
            mView.frame=CGRectMake(0, 0, 320, 568);
        }
        else
        {
            mView.frame=CGRectMake(0, 0, 320, 480);
        }
        
        [mView setBackgroundColor:[UIColor blackColor]];
        [mView setAlpha:0.5];
        [view addSubview:mView];
         
        UIImageView *imageView = [[UIImageView alloc] init];
        imageView.image=[UIImage imageNamed:@""];
        if(IS_IPHONE5)
        {
           [imageView setFrame:CGRectMake(0, 20, 320, 548)];
        }
        else
        {
            [imageView setFrame:CGRectMake(0, 20, 320, 460)];
        }
        [imageView setBackgroundColor:[UIColor clearColor]];
        [view addSubview:imageView];
        
		wait = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActionSheetStyleBlackTranslucent];
		wait.hidesWhenStopped = NO;
        if(IS_IPHONE5)
        {
          [wait setFrame:CGRectMake(145, 400, 30, 30)];
        }
        else
        {
           [wait setFrame:CGRectMake(145, 200, 30, 30)];
        }
        [imageView addSubview:wait];
        
        busyLabel = [[UILabel alloc] init];
        if(IS_IPHONE5)
        {
           busyLabel.frame=CGRectMake(20,360, 280, 60);
        }
        else
        {
            busyLabel.frame=CGRectMake(20,380, 280, 60);
        }
        busyLabel.textColor = [UIColor blackColor];
        busyLabel.numberOfLines = 2;
       // busyLabel.alpha = 0.7;
        busyLabel.backgroundColor = [UIColor clearColor];
        busyLabel.text =@"Processing Request... Please Wait";
        busyLabel.textAlignment = NSTextAlignmentCenter;
		[imageView addSubview:busyLabel];
        
		[wait startAnimating];
		
		return self;
	}
	
	return nil;
}
- (void) makeBusy:(BOOL)yesOrno
{
	if(yesOrno)
    {
		busyCount++;
	}else {
		busyCount--;
		if(busyCount<0){
			busyCount = 0;
		}
	}
	
	if(busyCount == 1){
		[[[UIApplication sharedApplication] keyWindow] addSubview:view];
		[[[UIApplication sharedApplication] keyWindow] bringSubviewToFront:view];
	}else if(busyCount == 0) {
		[view removeFromSuperview];
	}else {
		[[[UIApplication sharedApplication] keyWindow] bringSubviewToFront:view];
	}

}

- (void) forceRemoveBusyState{
	busyCount = 0;
	[view removeFromSuperview];
}
+ (ImpActivityAgent*)defaultAgent{
	if(!agent){
		agent =[[ImpActivityAgent alloc] myinit];
	}
	return agent;
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}

- (void)dealloc{
	[view release];
	[wait release];
	[busyLabel release];
	
	[super dealloc];
}
@end
