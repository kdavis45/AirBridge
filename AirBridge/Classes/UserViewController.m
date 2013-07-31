//
//  UserViewController.m
//
//  Created by Kerry Davis on 28/2/11.
//  Copyright 2010 mVeloce. All rights reserved.
//

#import "UserViewController.h"
#import "TSVPClientAppDelegate.h"

@implementation UserViewController

@synthesize webView = m_webView;
@synthesize urlString;
@synthesize text;

- (void) reloadData
{

//	NSString *body = [NSString stringWithFormat: @"parent_ID=%@", appDelegate.sessionID];
//	NSMutableURLRequest *request = [[[NSMutableURLRequest alloc]initWithURL: url] autorelease];
//	[request setHTTPMethod: @"POST"];
//	[request setHTTPBody: [body dataUsingEncoding: NSUTF8StringEncoding]];
//	[m_webView loadRequest: request];
	
	if (self.urlString != nil)
	{
		m_webView.dataDetectorTypes = UIDataDetectorTypeNone;
		NSURL *url = [NSURL URLWithString: self.urlString];
		[m_webView loadRequest:[NSURLRequest requestWithURL:url]];
		[[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
	}
	else
	{
		TSVPClientAppDelegate* appDelegate = (TSVPClientAppDelegate *)[[UIApplication sharedApplication] delegate];
		NSURL* l_path = [appDelegate applicationDocumentsDirectory];

		m_webView.dataDetectorTypes = UIDataDetectorTypeLink | UIDataDetectorTypePhoneNumber | UIDataDetectorTypeAddress | UIDataDetectorTypeCalendarEvent;
		[m_webView loadHTMLString:[NSString stringWithFormat:@"%@<p><p><img src=\"qrcode.png\">", self.text] baseURL:l_path];
	}
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad 
{
	[super viewDidLoad];
	
	if (self.urlString != nil)
	{
		[self.navigationController setNavigationBarHidden:YES animated:NO];
	}
	
	[self reloadData];
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
	[super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload 
{
	[super viewDidUnload];
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	
	self.webView = nil;
	
}

- (void)dealloc 
{
	self.webView = nil;
	self.urlString = nil;
	self.text = nil;
	
	[super dealloc];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
	[[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
	NSLog(@"webView didFailLoadWithError: %@", error);
//	[[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
	if (navigationType == UIWebViewNavigationTypeLinkClicked)
	{
		[[UIApplication sharedApplication] openURL:request.URL];
		return NO;
	}
	
	return YES;
}

@end
