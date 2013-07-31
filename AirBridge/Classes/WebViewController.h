//
//  WebViewController.h
//  OpenURL
//
//  Created by Chithra Nachiappan on 8/22/12.
//  Copyright (c) 2012 mVeloce. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WebViewController : UIViewController<UIWebViewDelegate>

@property(nonatomic,retain) IBOutlet UIWebView *webView;

@property(nonatomic,retain) IBOutlet UIView *view_indicator;

@property(nonatomic,retain) IBOutlet UIActivityIndicatorView *indicator;

-(void)webView_load;

@end
