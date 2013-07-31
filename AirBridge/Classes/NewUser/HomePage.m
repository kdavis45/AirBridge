//
//  HomePage.m
//  AirBridge
//
//  Created by Mamatha on 11/07/13.
//  Copyright (c) 2013 Mamatha. All rights reserved.
//

#import "HomePage.h"
#import "RegistrationPage.h"

@interface HomePage ()

@end

@implementation HomePage

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
    self.navigationController.navigationBarHidden = YES;
    
    RegistrationPage *loscr = [[RegistrationPage alloc] initWithNibName:nil bundle:nil];
    [self.navigationController pushViewController:loscr animated:YES];
    [loscr release];

    return;
}
@end
