//
//  ImpActivityAgent.h
//  Impressol Utility
//
//  Created by Development Team on 1/12/10.
//  Copyright 2010 Impressol. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ImpActivityAgent : NSObject <UINavigationControllerDelegate>{
	UIView* view;
    UIView *IndicatorView;
	UIActivityIndicatorView* wait;
	UILabel* busyLabel;
	int busyCount;
    UIButton *CancelButton;
}

/* Pass 'YES' if want to show activity indicator. 'NO' if you want to stop animating */
- (void) makeBusy:(BOOL)yesOrno;
- (void) forceRemoveBusyState;

+ (ImpActivityAgent*)defaultAgent;

@end
