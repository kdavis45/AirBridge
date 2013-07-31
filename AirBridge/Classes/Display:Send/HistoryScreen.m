//
//  HistoryScreen.m
//  AirBridge
//
//  Created by Imran2 on 03/07/13.
//  Copyright (c) 2013 Impressol. All rights reserved.
//

#import "HistoryScreen.h"
#import "ImpActivityAgent.h"
#import <QuartzCore/QuartzCore.h>
#import <MediaPlayer/MediaPlayer.h>

@interface HistoryScreen ()

@end

@implementation HistoryScreen
@synthesize videosArr;

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
	// Do any additional setup after loading the view.
    
    self.title=@"History Screen";
    
    
    
    self.navigationController.navigationBar.barStyle=UIBarStyleBlack;
    
    self.navigationItem.hidesBackButton=YES;
    
    Imageview=[[UIImageView alloc]init];
    Imageview.frame=CGRectMake(0, 0, 320, 416);
    
    Imageview.backgroundColor=[UIColor lightGrayColor];
    Imageview.userInteractionEnabled=YES;
    Imageview.image=[UIImage imageNamed:@"bg.png"];
    [self.view addSubview:Imageview];
    
    CameraButton=[UIButton buttonWithType:UIButtonTypeRoundedRect];
    CameraButton.frame=CGRectMake(30, 360, 50, 50);
    [CameraButton setBackgroundImage:[UIImage imageNamed:@"3.png"] forState:UIControlStateNormal];
    [CameraButton addTarget:self action:@selector(CameraButtonAction) forControlEvents:UIControlEventTouchUpInside];
    [Imageview addSubview:CameraButton];
    
    SocialButton=[UIButton buttonWithType:UIButtonTypeRoundedRect];
    SocialButton.frame=CGRectMake(130, 360, 50, 50);
    [SocialButton setBackgroundImage:[UIImage imageNamed:@"2.png"] forState:UIControlStateNormal];
    [SocialButton addTarget:self action:@selector(SocialButtonAction) forControlEvents:UIControlEventTouchUpInside];
    [Imageview addSubview:SocialButton];
    
    SettingsButton=[UIButton buttonWithType:UIButtonTypeRoundedRect];
    SettingsButton.frame=CGRectMake(240, 360, 50, 50);
    [SettingsButton setBackgroundImage:[UIImage imageNamed:@"1.png"] forState:UIControlStateNormal];
    [SettingsButton addTarget:self action:@selector(SettingsButtonAction) forControlEvents:UIControlEventTouchUpInside];
    [Imageview addSubview:SettingsButton];
    
    UIButton *BackButton=[UIButton buttonWithType:UIButtonTypeRoundedRect];
    BackButton.frame=CGRectMake(0,0, 45, 30);
    [BackButton setBackgroundImage:[UIImage imageNamed:@"Back.png"] forState:UIControlStateNormal];
    [BackButton addTarget:self action:@selector(BackButtonAction) forControlEvents:UIControlEventTouchUpInside];
    
    scrollView = [[UIScrollView alloc] init];
    [scrollView setFrame:CGRectMake(0, 0, 320, 350)];
    [scrollView setBackgroundColor:[UIColor clearColor]];
    [self.view addSubview:scrollView];
    
    
    
    
}
-(void)viewWillAppear:(BOOL)animated
{
    self.navigationItem.hidesBackButton = YES;
    self.navigationController.navigationBarHidden = NO;
    [[ImpActivityAgent defaultAgent] makeBusy:YES];
    
}

-(void)viewDidAppear:(BOOL)animated
{
    
    [[scrollView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
    [self getVideosList];
}

-(void)getVideosList
{
    NSString *urlString = @"http://airbridgelabs.com/airbridge/videolist.php";
    
    
    NSMutableURLRequest *request = [[[NSMutableURLRequest alloc] init] autorelease];
    [request setURL:[NSURL URLWithString:urlString]];
    [request setHTTPMethod:@"POST"];
    
    NSMutableData *body = [NSMutableData data];
    
    NSString *boundary = @"---------------------------14737809831466499882746641449";
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@", boundary];
    [request addValue:contentType forHTTPHeaderField:@"Content-Type"];
    
    
    // close form
    [body appendData:[[NSString stringWithFormat:@"--%@--\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    // set request body
    [request setHTTPBody:body];
    
    
    NSString *msgLength = [NSString stringWithFormat:@"%d", [body length]];
    [request addValue: msgLength forHTTPHeaderField:@"Content-Length"];
    NSURLResponse *response = NULL;
    NSError *requestError = NULL;
    NSData *responseData1 = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&requestError];
    
    NSString *responseString = [[[NSString alloc] initWithData:responseData1 encoding:NSUTF8StringEncoding] autorelease];
    
    [[ImpActivityAgent defaultAgent] makeBusy:NO];
    NSLog(@"responseString == %@",responseString);
    
    NSDictionary *dict = [responseString JSONValue];
    self.videosArr = [dict objectForKey:@"video_users"];
    NSLog(@"arr ===%@",self.videosArr);
    
    [self createVidoesView];
    
    
}

-(void)createVidoesView
{
    int x_Cord=10;
    
    int y_cord=10;
    
    
    
    for (int i=0; i<[self.videosArr count]; i++)
    {
        UIButton *likeBtn=[UIButton buttonWithType:UIButtonTypeRoundedRect];
        likeBtn.frame=CGRectMake(x_Cord, y_cord, 60, 60);
        likeBtn.tag=i;
        [likeBtn setUserInteractionEnabled:NO];
        [scrollView addSubview:likeBtn];
        
        
        likeBtn.layer.cornerRadius = 8;
        likeBtn.layer.borderColor = [UIColor blackColor].CGColor;
        likeBtn.layer.borderWidth = 2;
        [likeBtn setBackgroundColor:[UIColor colorWithRed:(255/255.0) green:(180/255.0) blue:(200/255.0) alpha:1]];
        likeBtn.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
        [likeBtn setTitle:@"Like" forState:UIControlStateNormal];
        
        
        
        
        
        UIView *view = [[UIView alloc] init];
        [view setFrame:CGRectMake(x_Cord +70, y_cord, 230, 60)];
        [view setBackgroundColor:[UIColor lightGrayColor]];
        
        view.layer.cornerRadius = 8;
        view.layer.borderColor = [UIColor blueColor].CGColor;
        view.layer.borderWidth = 2;
        [scrollView addSubview:view];
        

        
        
        NSDictionary *dict = [self.videosArr objectAtIndex:i];
        NSArray *Arr = [[dict objectForKey:@"video"] componentsSeparatedByString:@"/"];
        NSString *url = [NSString stringWithFormat:@"http://airbridgelabs.com/airbridge/%@",[dict objectForKey:@"video"]];
        url = [url stringByReplacingOccurrencesOfString:@" " withString:@"%20"];
        NSLog(@"url===%@",url);
        
        UILabel *lolabel = [[UILabel alloc] init];
        [lolabel setFrame:CGRectMake(60, 15, 150, 40)];
        [lolabel setFont:[UIFont systemFontOfSize:13.0]];
        [lolabel setBackgroundColor:[UIColor clearColor]];
        
        if([Arr count] > 0)
        {
            NSString *loname = [Arr lastObject];
            NSArray *loarr = [loname componentsSeparatedByString:@"_"];
            if([loarr count] > 0)
            {
                [lolabel setText:[loarr lastObject]];
            }
            else
            {
                [lolabel setText:[Arr lastObject]];
            }
            
        }
        [view addSubview:lolabel];
        
        
        
        
        
        
        
        
       UIWebView *webView = [[UIWebView alloc] init];
        ;
        [webView setFrame:CGRectMake(10, 10, 40, 40)];
        
        
        webView.delegate = self;
        [webView setBackgroundColor:[UIColor blackColor]];
        [webView setOpaque:NO];
        
        [view addSubview:webView];
        
        NSURL *lourl = [NSURL URLWithString:url];
        
        
        
        NSString *fileExtension = [lourl pathExtension];
        NSLog(@"file extension===%@",fileExtension);
        if([fileExtension compare:@"MOV"] == NSOrderedSame)
        {
            webView.mediaPlaybackAllowsAirPlay = YES;
            NSString *htmlString  = @"";
            if (([[[UIDevice currentDevice] systemVersion] compare:@"6.0" options:NSNumericSearch] != NSOrderedAscending)){
                
                //si estamos en iOS6 cambiamos la URL por la nueva con /embed/
                url = [url stringByReplacingOccurrencesOfString:@"/watch?v=" withString:@"/embed/"];
                
                
                //Usamos un iframe para embeber el vídeo en el webview
                htmlString = [NSString stringWithFormat:@"<html><head><body style=\"margin:0;background:#000000\"><iframe src=\"%@?rel=0&showinfo=0&&fs=1\"  width=\"40\" height=\"40\" frameborder=\"0\" allowfullscreen /></body></html>",  url];
            }
            else
            { //si estamos en iOS5, podemos seguir usando tanto la URL como el código anterior para embeber el vídeo
                url = [NSString stringWithFormat:@"<html><head><meta name = \"viewport\" content = \"initial-scale = 1.0, user-scalable = no, width = 40\"/></head><body style=\"background:#000000;margin-top:0px;margin-left:0px\"><div><object width=\"40\" height=\"40\"><param name=\"movie\" value=\"%@\"></param><param name=\"wmode\" value=\"transparent\"></param><embed src=\"%@\"type=\"application/x-shockwave-flash\" wmode=\"transparent\" width=\"40\" height=\"40\"></embed></object></div></body></html>",url,  url];
            }
            
            [webView loadHTMLString:htmlString baseURL:[NSURL URLWithString:url]];
        }
        else
        {
            [webView loadRequest:[NSURLRequest requestWithURL:lourl]];
        }

        
       
        
        

        
        
        
        UIButton *viewBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [viewBtn setFrame:CGRectMake(x_Cord +70, y_cord, 230, 60)];
        [viewBtn setTag:i];
        [viewBtn addTarget:self action:@selector(viewBtn_action:) forControlEvents:UIControlEventTouchUpInside];
        [viewBtn setBackgroundColor:[UIColor clearColor]];
        [scrollView addSubview:viewBtn];
        
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(longPress:)];
        longPress.minimumPressDuration = 1.0;
        longPress.delaysTouchesEnded = YES;
        [viewBtn addGestureRecognizer:longPress];
        [longPress release];
        
        
        
        
        x_Cord=10;
        y_cord=y_cord+70;
        
        scrollView.contentSize=CGSizeMake(320, y_cord);
        [webview release];
        
        //        [likeBtn release];
        //        [web release];
        //        [lolabel release];
        //        [view release];
        
    }
    [[ImpActivityAgent defaultAgent] makeBusy:NO];
}


-(void)BackButtonAction
{
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)CameraButtonAction
{
    printf("CameraButtonAction..."); UIImagePickerController * picker1 = [[UIImagePickerController alloc] init];
    picker1.delegate = self;
    NSArray *mediaTypesAllowed=[[NSArray alloc]init];
    mediaTypesAllowed = [UIImagePickerController availableMediaTypesForSourceType:UIImagePickerControllerSourceTypeSavedPhotosAlbum];
    [picker1 setMediaTypes:mediaTypesAllowed];
    [self presentViewController:picker1 animated:YES completion:nil];
}



- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    
    //assign the mediatype to a string
    NSString *mediaType = [info objectForKey:UIImagePickerControllerMediaType];
    
    //check the media type string so we can determine if its a video
    
    
    
    if ([mediaType isEqualToString:@"public.movie"])
    {
        NSLog(@"got a movie");
        NSURL *videoURL = [info objectForKey:UIImagePickerControllerMediaURL];
        NSData *webData = [NSData dataWithContentsOfURL:videoURL];
        
        [[ImpActivityAgent defaultAgent] makeBusy:YES];
        //[self post:webData];
        [self dismissViewControllerAnimated:YES completion:nil];
        [self sendRequest:webData];
        isVideo = YES;
        
        
    }
    else
    {
        UIImage *galaryImage = [info valueForKey:@"UIImagePickerControllerOriginalImage"];
        
        NSLog(@"galaryImage==%@",galaryImage);
        id imagename = (NSString *)[info valueForKey:@"UIImagePickerControllerOriginalImage"];
        
        //[lo_nofile setBackgroundColor:[UIColor grayColor]];
        if(imagename == [NSNull null] )
        {
            printf("null");
            
        }
        else
        {
            printf(" not null");
            
            NSData *webData = UIImagePNGRepresentation(galaryImage);
            [self dismissViewControllerAnimated:YES completion:nil];
            [self sendRequest:webData];
            isVideo = NO;
        }
        
        
    }
    
    
    
    
}

-(void)sendRequest:(NSData *)data
{
    
    if([self checkNetworkStatus] == 0)
    {
        NSString *userID = [NSString stringWithFormat:@"%d",[[NSUserDefaults standardUserDefaults] integerForKey:@"userID"]];
        
        NSArray *loKeys = [NSArray arrayWithObjects:@"name",@"uid", nil];
        
        NSArray *loVal = [NSArray arrayWithObjects:@"mamatha",userID, nil];
        
        NSString *loUrl = [NSString stringWithFormat:@"http://airbridgelabs.com/airbridge/videosuploade.php?"];
        ServerCode *loServer = [[ServerCode alloc]init];
        NSString *responseString = @"";
        if(isVideo)
        {
            responseString = [loServer getResponseByPostRequestWith_Video_URL:loUrl WithKeys:loKeys withObjects:[NSDictionary dictionaryWithObjects:loVal forKeys:loKeys] withVideo:data withName:@""];
        }
        else if(!isVideo)
        {
            UIImage *img = [UIImage imageWithData:data];
            responseString = [loServer getResponseByPostRequestWith_URL:loUrl WithKeys:loKeys withObjects:[NSDictionary dictionaryWithObjects:loVal forKeys:loKeys] withImage:img withName:@""];
        }
       
        NSLog(@"response string===%@",responseString);
        
        if([responseString isEqualToString:@"0"])
        {
            [[ImpActivityAgent defaultAgent] makeBusy:NO];
            
            [[[[UIAlertView alloc] initWithTitle:nil message:@"Please check the fields and try again." delegate:self cancelButtonTitle:@"Ok" otherButtonTitles: nil] autorelease] show];
        }
        else
        {
            [[ImpActivityAgent defaultAgent] makeBusy:NO];
            
            UIAlertView *loAlert = [[UIAlertView alloc] initWithTitle:nil message:@"Data has sent successfully." delegate:self cancelButtonTitle:@"Ok" otherButtonTitles: nil];
            [loAlert setTag:12345];
            [loAlert show];
            [loAlert release];
        }
    }
    else
    {
        [[ImpActivityAgent defaultAgent] makeBusy:NO];
        
        [[[[UIAlertView alloc] initWithTitle:@"Sorry!" message:@"Network is not available." delegate:self cancelButtonTitle:@"Ok" otherButtonTitles: nil] autorelease] show];
    }
    
    
}


-(void)SocialButtonAction
{
    printf("SocialButtonAction...");
    
    ContentSelectionScreen *Screen=[[ContentSelectionScreen alloc]initWithNibName:nil bundle:nil];
    [self.navigationController pushViewController:Screen animated:YES];
}

-(void)SettingsButtonAction
{
    printf("SettingsButtonAction...");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    printf("*************");
    if (toInterfaceOrientation==UIInterfaceOrientationLandscapeRight)
    {
        printf("UIInterfaceOrientationLandscapeRight");
        landOrient = 1;
        Imageview.frame=CGRectMake(0, 0, 480, 320);
        CameraButton.frame=CGRectMake(60, 210, 50, 50);
        SocialButton.frame=CGRectMake(190, 210, 50, 50);
        SettingsButton.frame=CGRectMake(360, 210, 50, 50);
        [scrollView setFrame:CGRectMake(0, 0, 480, 200)];
        if(player1)
        {
            player1.view.frame = CGRectMake(0,0, 480,320);
        }
         
        
    }
    else if (toInterfaceOrientation==UIInterfaceOrientationLandscapeLeft)
    {
        printf("UIInterfaceOrientationLandscapeLeft");
        landOrient = 1;
        Imageview.frame=CGRectMake(0, 0, 480, 320);
        CameraButton.frame=CGRectMake(60, 210, 50, 50);
        SocialButton.frame=CGRectMake(190, 210, 50, 50);
        SettingsButton.frame=CGRectMake(360, 210, 50, 50);
        [scrollView setFrame:CGRectMake(0, 0, 480, 200)];
        if(player1)
        {
            player1.view.frame = CGRectMake(0,0, 480,320);
        }
        
    }
    else if (toInterfaceOrientation==UIInterfaceOrientationPortrait)
    {
        printf("UIInterfaceOrientationPortrait");
        landOrient = 0;
        Imageview.frame=CGRectMake(0, 0, 320, 416);
        CameraButton.frame=CGRectMake(30, 360, 50, 50);
        SocialButton.frame=CGRectMake(130, 360, 50, 50);
        SettingsButton.frame=CGRectMake(240, 360, 50, 50);
        [scrollView setFrame:CGRectMake(0, 0, 320, 350)];
        if(player1)
        {
            player1.view.frame = CGRectMake(0,0, 320,440);
        }
        
        
        
    }
    else if (toInterfaceOrientation==UIInterfaceOrientationPortraitUpsideDown)
    {
        printf("UIInterfaceOrientationPortraitUpsideDown");
        landOrient = 0;
        Imageview.frame=CGRectMake(0, 0, 320, 416);
        CameraButton.frame=CGRectMake(30, 360, 50, 50);
        SocialButton.frame=CGRectMake(130, 360, 50, 50);
        SettingsButton.frame=CGRectMake(240, 360, 50, 50);
        [scrollView setFrame:CGRectMake(0, 0, 320, 350)];
        if(player1)
        {
            player1.view.frame = CGRectMake(0,0, 320,440);
        }
        
    }
}

-(void)viewBtn_action:(id)sender
{
    UIButton *lobtn = (UIButton *)sender;
    NSLog(@"frame===x==%f,y==%f",lobtn.frame.origin.x,lobtn.frame.origin.y);
    
    
    NSLog(@"videosArr===%@",self.videosArr);
    NSDictionary *dict = [videosArr objectAtIndex:lobtn.tag];
    NSLog(@"dict===%@",dict);
    NSString *url = [NSString stringWithFormat:@"http://airbridgelabs.com/airbridge/%@",[dict objectForKey:@"video"]];
    url = [url stringByReplacingOccurrencesOfString:@" " withString:@"%20"];
    NSLog(@"url===%@",url);
    
    DisplayScreen *loscr = [[DisplayScreen alloc] initWithNibName:nil bundle:nil];
    loscr.url = url;
    [self.navigationController pushViewController:loscr animated:YES];
    [loscr release];
    
    
    
   
   
    
    
}


- (void)longPress:(UILongPressGestureRecognizer*)gesture {
    NSLog(@"tag ===%d",gesture.view.tag);
    NSLog(@"frame===x==%f,y==%f",gesture.view.frame.origin.x,gesture.view.frame.origin.y);
    
    if (gesture.state == UIGestureRecognizerStateEnded) {
        NSLog(@"UIGestureRecognizerStateEnded");
                //Do Whatever You want on End of Gesture
    }
    else if (gesture.state == UIGestureRecognizerStateBegan){
        NSLog(@"UIGestureRecognizerStateBegan.");
        UIButton *delBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [delBtn setFrame:CGRectMake(gesture.view.frame.origin.x+205, gesture.view.frame.origin.y-5, 30, 30)];
        [delBtn addTarget:self action:@selector(delVideo_Action:) forControlEvents:UIControlEventTouchUpInside];
        [delBtn setTag:gesture.view.tag];
        [scrollView addSubview:delBtn];

        //Do Whatever You want on Began of Gesture
    }
    else if (gesture.state == UIGestureRecognizerStatePossible)
    {
        
    }
    
       
}

-(void)delVideo_Action:(id)sender
{
    printf("remove the del button");
    UIButton *lobtn = (UIButton *)sender;
    [lobtn removeFromSuperview];
    
}


- (NSInteger)checkNetworkStatus
{
	if ([[Reachability reachabilityForInternetConnection] currentReachabilityStatus] == NotReachable )
    {
		return -1;
	}
	else
	{
		return 0;
	}
}

- (BOOL)shouldAutorotate {
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}
// pre-iOS 6 support
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    return (toInterfaceOrientation == UIInterfaceOrientationPortrait);
}


@end
