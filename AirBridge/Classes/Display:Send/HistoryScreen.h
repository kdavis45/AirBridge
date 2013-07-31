//
//  HistoryScreen.h
//  AirBridge
//
//  Created by Imran2 on 03/07/13.
//  Copyright (c) 2013 Impressol. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

@interface HistoryScreen : UIViewController<UINavigationControllerDelegate,UIImagePickerControllerDelegate,UIScrollViewDelegate,UIWebViewDelegate>
{
    UIScrollView *scrollView;
    
    UIImageView *Imageview;
    UIButton *CameraButton,*SocialButton,*SettingsButton;
    int landOrient,delCreate;
    UIWebView *webview;
    MPMoviePlayerController *player1;
    BOOL isVideo;
}

@property(strong , nonatomic)NSArray *videosArr;
@end
