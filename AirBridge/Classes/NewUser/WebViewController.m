//
//  WebViewController.m
//  OpenURL
//
//  Created by Chithra Nachiappan on 8/22/12.
//  Copyright (c) 2012 mVeloce. All rights reserved.
//

#import "WebViewController.h"

@interface WebViewController ()

@end

@implementation WebViewController
@synthesize view_indicator=_view_indicator;
@synthesize indicator=_indicator;
@synthesize webView=_webView;

-(void)killWebView
{
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    self.title=@"WebView";
    self.navigationController.navigationBar.tintColor=[UIColor blackColor];

    [self performSelector:@selector(webView_load) withObject:nil afterDelay:0.5];
    
  
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

//extern long long vid1;
//extern void cvt2longUrl(unsigned long long url, unsigned char *p);
extern char oldURL[];

// Looper  http://youtu.be/X16RjlJLpUQ
// Promethius  http://youtu.be/1byZkbNB3Jw
//    http://youtu.be/s-3kW0wEQIQ s-3kW0wEQIQ does not work on mobile
//http://www.youtube.com/v/Wriy3ICfF9U Wriy3ICfF9U does not work on mobile
// goo.gl/PHJcB ....short google url for mcDonalds
// http://goo.gl/NsiJ short code for staples
// http://goo.gl/SDut pinterest/Target
// SO-iTFdDb6I Girlscout video
// 2ng gs movie http://youtu.be/HJhchLeR1X0
// http://goo.gl/7YpBw girl scout cookie faq http://www.girlscouts.org/program/gs_cookies/faq.asp
// girlscout app https://itunes.apple.com/us/app/girl-scout-cookie-finder/id 593932097 ?mt=8 http://goo.gl/N9pZ6

/*
 UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectMake(10, 10, 300, 600)];
 
 NSURL *targetURL = [NSURL URLWithString:[NSString stringWithFormat:@"%s",oldURL]];
 NSURLRequest *request = [NSURLRequest requestWithURL:targetURL];
 [webView loadRequest:request];
 
 [self.view addSubview:webView];
 [webView release];
 
 */

-(void)webView_load
{
    
    //    NSString *str_url=[NSString stringWithFormat:@"https://www.mfortune.co.uk/games/fm/index.php"];
    //    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@",str_url]];

    self.view_indicator.hidden=TRUE;
    
    self.webView.scalesPageToFit = YES;
    self.webView.autoresizesSubviews = YES;
    self.webView.autoresizingMask=(UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth);
    self.webView.delegate=self;
    
//    NSString *stringURL = [NSString stringWithFormat:@"http://www.goo.gl/%s",oldURL];
    NSString *stringURL = [NSString stringWithFormat:@"%s",oldURL];
    NSURL *url = [NSURL URLWithString:stringURL];
    
//    NSURLRequest *url_request = [NSURLRequest requestWithURL:url];
    
//    NSURLRequest *url_request = [NSURLRequest requestWithURL:url cachePolicy:NSURLCacheStorageAllowed timeoutInterval:10];
    NSURLRequest *url_request = [NSURLRequest requestWithURL:url];

    [self.webView loadRequest:url_request];
    
}

#pragma mark -
#pragma mark WebView Delegates

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    self.view_indicator.hidden=FALSE;
    [self.indicator startAnimating];
    

}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    self.view_indicator.hidden=TRUE;
    [self.indicator stopAnimating];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    
    UIAlertView * errorAlert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"No internet connection" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[errorAlert show];
    
    self.view_indicator.hidden=TRUE;
    [self.indicator stopAnimating];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.webView stopLoading];
    self.webView.delegate = nil;
}
- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
