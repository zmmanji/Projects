//
//  LoginMain.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 07/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <sqlite3.h>

@interface LoginMain : UIViewController
{
    sqlite3 *contactDB;
    
    UITextField *usernameField;
    UITextField *passwordField;
    UITextField *confirmPassword;
    
    UILabel *status;
    
    NSString *databasePath;
}

@property (weak, nonatomic) IBOutlet UITextField *username;

@property (weak, nonatomic) IBOutlet UITextField *password;
@property (weak, nonatomic) IBOutlet UILabel *Regsiter;

@property (weak, nonatomic) IBOutlet UIButton *Login;
@property (weak, nonatomic) IBOutlet UILabel *AccountType;
- (IBAction)Register:(id)sender;
@property (weak, nonatomic) IBOutlet UIImageView *Image1;

- (IBAction)LoginUser:(id)sender;
@end
