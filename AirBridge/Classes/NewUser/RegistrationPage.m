//
//  RegistrationPage.m
//  AirBridge
//
//  Created by Mamatha on 11/07/13.
//  Copyright (c) 2013 Mamatha. All rights reserved.
//

#import "RegistrationPage.h"
#import "AppDelegate.h"
#import <QuartzCore/QuartzCore.h>
#import "ImpActivityAgent.h"
//#include <Accelerate/Accelerate.h>
#import "GraphView.h"
#import "PulseFilterAPI.h"
#import "WebViewController.h"

#define kAppIconSize 60
#define APP_ID @"fd725621c5e44198a5b8ad3f7a0ffa09"

@interface RegistrationPage ()

@end

@implementation RegistrationPage

//GraphView *graphView;
//extern unsigned int     audioValues[];
//extern int MicBufferCount;
//extern SInt16	originalReal[]; // will never be more than 1/2 second
//extern COMPLEX_SPLIT ASmall;
//extern FFTSetup        setupRealSmall;

static AIR_BRIDGE_MESSAGE newMessage;
static id          thisClass; // IMPORTANT: This should be defined as static.


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
extern char oldURL[];

- (void) processSURLBeacon:(char *)url
{
    WebViewController *webViewController;
    
    sprintf(oldURL, "%s",url);
    
    webViewController=[[WebViewController alloc] initWithNibName:@"WebViewController" bundle:nil];
    
    [self.navigationController pushViewController:webViewController animated:YES];
//    [webViewController release];
    
}

-(void) AudioProcessingDidReceiveMessage:(AIR_BRIDGE_MESSAGE)msg
{

    char *msgptr = (char *)&msg.msgbody[0];
    
    NSURL *dURL = [NSURL URLWithString:[NSString stringWithFormat:@"%s",msgptr]];
                   
    if ([[UIApplication sharedApplication] canOpenURL:dURL])
    {
        [[UIApplication sharedApplication] openURL:dURL];
        exit (0);
    }

    [self processSURLBeacon:msgptr];
}

void cProcessAudioMessage(AIR_BRIDGE_MESSAGE *msg) // call back to here from pulsefilter
{
    if (msg->hdr.venueID)
    {
        playSysTone (SYSSUCCESSTONE);

    }
    else
    {
        playSysTone (SYSFAILTONE);
    }
    
    
    // *msg is ignored because it should always be newMessage
    [thisClass AudioProcessingDidReceiveMessage:newMessage];
        
    continueAirBridge();

}

/*
- (void) waitForGraphView
{
    
    for (int y = 0; y < 128; y+=2)
    {
        int z = MicBufferCount+y;
        ASmall.realp[y/2] = (float)originalReal[z];
        ASmall.imagp[y/2] = (float)originalReal[z+1];
    }
    
    // Carry out a Forward transform.
    vDSP_fft_zrip(setupRealSmall, &ASmall, 1, 7, FFT_FORWARD);
    
    double biggest = 0;
    
    for (int x = 32; x < 64; ++x)
    {
        double val;
        val = (ASmall.realp[x]*ASmall.realp[x] + ASmall.imagp[x]*ASmall.imagp[x]);
        if (val > biggest)
        {
            biggest = val;
        }
        audioValues[x-32] = (int)val;
    }
    if (biggest > 65535.0)
    {
        if (biggest > (double)2147483647) // max biggest to 31 bits
        {
            biggest = 2147483647;
        }
        
        biggest = 65535.0/biggest; // normalize to 16 bits unsigned
    }
    else
    {
        biggest = 1;
    }
    //    int level = 65535;
    
    for (int x = 0; x < 32; ++x)
    {
        audioValues[x] = (unsigned int) (((double)audioValues[x])*biggest);
        if (audioValues[x] < 10)
        {
            audioValues[x] = 10;
        }
    }
    
    //    [graphView resetGraph];
    [graphView setNeedsDisplay];
    
    [self performSelector:@selector(waitForGraphView) withObject:nil afterDelay:(PROCESSMICDELAY)];
    
}
*/
- (void)viewDidLoad
{
    
    thisClass = self; // get the instance pointer for this class for C to OBJ-C interface

    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"bg_320_460.png"]];
    
    self.navigationController.navigationBar.barStyle=UIBarStyleBlack;
    
    self.title=@"AirBridge Demo";
    
//    graphView = [[GraphView alloc]initWithFrame:CGRectMake(60, 20, 192, 30)];
    //    [graphView setBackgroundColor:[UIColor blackColor]];
//    [graphView setBackgroundColor:[UIColor clearColor]];
//    [self.view addSubview:graphView];
    
    airBridgeInit ((AIR_BRIDGE_MESSAGE *)&newMessage, &cProcessAudioMessage);

    continueAirBridge();
    
//    [self performSelector:@selector(waitForGraphView) withObject:nil afterDelay:PROCESSMICDELAY];

    UILabel *firstLabel=[[UILabel alloc] init];
    firstLabel.frame=CGRectMake(10,120, 100, 30);
    firstLabel.text=@"Link 1:";
    [firstLabel setShadowColor:[UIColor blackColor]];
    firstLabel.textAlignment=NSTextAlignmentLeft;
    firstLabel.backgroundColor=[UIColor clearColor];
    [self.view addSubview:firstLabel];
    
    
    firstField=[[UITextField alloc] init];
    firstField.frame=CGRectMake(70, 120, 240, 30);
    firstField.backgroundColor=[UIColor whiteColor];
    [firstField setBorderStyle:UITextBorderStyleLine];
    firstField.textAlignment=NSTextAlignmentCenter;
    firstField.autocapitalizationType=UITextAutocapitalizationTypeNone;
    firstField.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
    firstField.font=[UIFont systemFontOfSize:16.0];
    firstField.delegate=self;
    firstField.text=@"www.airbridgelabs.com/link1.jpg";
    [firstField setUserInteractionEnabled:YES];
    [self.view addSubview:firstField];
    
    
    UILabel *lastLabel=[[UILabel alloc] init];
    lastLabel.frame=CGRectMake(10, 160, 100, 30);
    [lastLabel setShadowColor:[UIColor blackColor]];
    lastLabel.text=@"Link 2:";
    lastLabel.textAlignment=NSTextAlignmentLeft;
    lastLabel.backgroundColor=[UIColor clearColor];
    [self.view addSubview:lastLabel];
    
    lastField=[[UITextField alloc] init];
    lastField.frame=CGRectMake(70, 160, 240, 30);
    lastField.backgroundColor=[UIColor whiteColor];
    [lastField setBorderStyle:UITextBorderStyleLine];
    lastField.textAlignment=NSTextAlignmentCenter;
    lastField.autocapitalizationType=UITextAutocapitalizationTypeNone;
    lastField.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
    lastField.font=[UIFont systemFontOfSize:16.0];
    lastField.delegate=self;
    lastField.text=@"www.airbridgelabs.com/link2.jpg";

    [lastField setUserInteractionEnabled:YES];
    [self.view addSubview:lastField];

    registerBtn=[UIButton buttonWithType:UIButtonTypeCustom];
    registerBtn.frame=CGRectMake(30,300,260, 40);
    [registerBtn setTitle:@"AirMail Link 1 (No Sound)" forState:UIControlStateNormal];
    registerBtn.titleLabel.font=[UIFont boldSystemFontOfSize:16.0];
    registerBtn.tag = 1;
    [registerBtn setBackgroundImage:[UIImage imageNamed:@"260_40.png"] forState:UIControlStateNormal];
    [registerBtn addTarget:self action:@selector(registerBtnAction) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:registerBtn];
    
    registerBtn2=[UIButton buttonWithType:UIButtonTypeCustom];
    registerBtn2.frame=CGRectMake(30,360,260, 40);
    [registerBtn2 setTitle:@"AirMail link 2 (Sound Effect)" forState:UIControlStateNormal];
    registerBtn2.titleLabel.font=[UIFont boldSystemFontOfSize:16.0];
    registerBtn2.tag = 1;
    [registerBtn2 setBackgroundImage:[UIImage imageNamed:@"260_40.png"] forState:UIControlStateNormal];
    [registerBtn2 addTarget:self action:@selector(registerBtnAction2) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:registerBtn2];
    
    [super viewDidLoad];
    
}

-(void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.hidesBackButton = YES;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma Mark - TextField delegate methods
-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    if(textField==firstField)
    {
        firstField.text = @"";
    }
    else if(textField==lastField)
    {
        lastField.text = @"";
    }
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];

    [[NSUserDefaults standardUserDefaults] setObject:firstField.text forKey:@"firstField"];
    [[NSUserDefaults standardUserDefaults] setObject:lastField.text forKey:@"lastField"];
//    UIImage *img = ImageButton.imageView.image;
    
//    [[NSUserDefaults standardUserDefaults] setObject:UIImagePNGRepresentation(img) forKey:@"profileImag"];
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.3];
    [self.view setFrame:CGRectMake(0,0, 320, 480)];
    [UIView commitAnimations];
    
    return YES;
}

-(void)ResignFirstResponderMethod
{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.3];
    [self.view setFrame:CGRectMake(0,0, 320, 480)];
    [UIView commitAnimations];
    
    [firstField resignFirstResponder];
    [lastField resignFirstResponder];
}


#pragma Mark - Button actions

-(void)registerBtnAction2
{
    [[ImpActivityAgent defaultAgent] makeBusy:YES];
    
    [[NSUserDefaults standardUserDefaults] setObject:lastField.text forKey:@"lastField"];
    if([firstField.text length] == 0)
    {
        [self showAlert:@"Link 2 can not be empty" withMEssage:@"Enter Link 2"];
    }
    else
    {
        AIR_BRIDGE_MESSAGE msg;
        char *p = (char *)[lastField.text UTF8String];
        char *p2;
        
        if ((p[0] == 'h'&& p[1] == 't' && p[2] == 't' && p[3] == 'p') || (p[0] == 'w'&& p[1] == 'w' && p[2] == 'w'))
        {
            
            p2 = airBridgeShortenURL (p);
            lastField.text = [NSString stringWithFormat:@"%s",p2];
        }
        else
        {
            p2 = p;
        }
        
        char *msgptr = (char *)&msg.msgbody[0];
        int x;
        
        for (x = 0; p2[x] && x < 17; ++x)
        {
            msgptr[x] = p2[x];
        }
        
        msgptr[x] = 0;
        sendAirBridge (&msg, 1);
    }

    [[ImpActivityAgent defaultAgent] makeBusy:NO];

}

-(void)registerBtnAction
{
    [[ImpActivityAgent defaultAgent] makeBusy:YES];
    
    [[NSUserDefaults standardUserDefaults] setObject:firstField.text forKey:@"firstField"];
    
    if([firstField.text length] == 0)
    {
        [self showAlert:@"Link 1 can not be Empty" withMEssage:@"Enter Link 1"];
    }
    else
    {
        AIR_BRIDGE_MESSAGE msg;
        char *p = (char *)[firstField.text UTF8String];
        char *p2;
        
        if ((p[0] == 'h'&& p[1] == 't' && p[2] == 't' && p[3] == 'p') || (p[0] == 'w'&& p[1] == 'w' && p[2] == 'w'))
        {
            p2 = airBridgeShortenURL (p);
            firstField.text = [NSString stringWithFormat:@"%s",p2];
        }
        else
        {
            p2 = p;
        }

        char *msgptr = (char *)&msg.msgbody[0];
        int x;
        
        for (x = 0; p2[x] && x < 17; ++x)
        {
            msgptr[x] = p2[x];
        }
        
        msgptr[x] = 0;
        sendAirBridge (&msg, 0);
    }
    [[ImpActivityAgent defaultAgent] makeBusy:NO];
}

#pragma Mark - Alert MEssage method
-(void)showAlert:(NSString *)title withMEssage:(NSString *)msg
{
    UIAlertView *Alert=[[UIAlertView alloc]initWithTitle:title message:msg delegate:self cancelButtonTitle:@"Ok" otherButtonTitles: nil];
    [Alert show];
    [Alert release];
}

@end
