//
//  DisplayScreen.h
//  AirBridge
//
//  Created by Mamatha on 16/07/13.
//  Copyright (c) 2013 Mamatha. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

@interface DisplayScreen : UIViewController<UIWebViewDelegate>
{
    UIWebView *webview;
    MPMoviePlayerController *player1;
}
@property(nonatomic,strong)NSString *url;

@end
