//
//  UserViewController.h
//
//  Created by Kerry Davis on 28/2/11.
//  Copyright 2010 mVeloce. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface UserViewController : UIViewController <UIWebViewDelegate>
{
	UIWebView *m_webView;
}

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, copy) NSString *urlString;
@property (nonatomic, copy) NSString *text;

@end
