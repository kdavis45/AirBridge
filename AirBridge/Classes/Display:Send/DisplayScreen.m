//
//  DisplayScreen.m
//  AirBridge
//
//  Created by Mamatha on 16/07/13.
//  Copyright (c) 2013 Mamatha. All rights reserved.
//

#import "DisplayScreen.h"
#import "ImpActivityAgent.h"

@interface DisplayScreen ()

@end

@implementation DisplayScreen
@synthesize url;

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
    [super viewDidLoad];
    
    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"bg_320_460.png"]];
    
    self.navigationController.navigationBar.barStyle=UIBarStyleBlack;
    
    [[ImpActivityAgent defaultAgent] makeBusy:YES];
   

	// Do any additional setup after loading the view.
}
-(void)viewDidAppear:(BOOL)animated
{
    NSURL *lourl = [NSURL URLWithString:self.url];
	
    
    
    NSString *fileExtension = [lourl pathExtension];
    NSLog(@"file extension===%@",fileExtension);
    if([fileExtension compare:@"MOV"] == NSOrderedSame)
    {
        player1 = [[MPMoviePlayerController alloc] initWithContentURL:[NSURL URLWithString:self.url] ];
        player1.view.frame = CGRectMake(10,10, 300,400);
        player1.view.backgroundColor = [UIColor clearColor];
        player1.scalingMode = MPMovieScalingModeNone;
        [player1 prepareToPlay];
        [player1 play];
        [self.view addSubview:player1.view];
        
    }
    else
    {
        UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:lourl]];
        
        UIImageView *imgView = [[UIImageView alloc] init];
        [imgView setFrame:CGRectMake(10, 10, 300, 400)];
        [imgView setImage:img];
        [self.view addSubview:imgView];
    }
    [[ImpActivityAgent defaultAgent] makeBusy:NO];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
