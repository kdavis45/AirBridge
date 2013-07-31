//
//  RegistrationPage.h
//  AirBridge
//
//  Created by Mamatha on 11/07/13.
//  Copyright (c) 2013 Mamatha. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RegistrationPage : UIViewController<UITextFieldDelegate,UIImagePickerControllerDelegate,UINavigationControllerDelegate,UIActionSheetDelegate>
{
    
    UITextField *firstField,*lastField;
    
    UIButton *registerBtn,*ImageButton;
    UIButton *registerBtn2;
//    UIImageView  *imgViewBG;
}
@property (nonatomic,retain) NSMutableData *ResponseData;
@property  NSInteger UpdateAction;

@end
