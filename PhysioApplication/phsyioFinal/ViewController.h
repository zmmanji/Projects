//
//  ViewController.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 07/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <sqlite3.h>


@interface ViewController : UIViewController
{
    sqlite3 *contactDB;
    
    UITextField *usernameField;
    UITextField *passwordField;
    UITextField *confirmPassword;
    
    UILabel *status;
    
    NSString *databasePath;
}
@property (retain, nonatomic) IBOutlet UITextField *usernameField;
@property (retain, nonatomic) IBOutlet UITextField *passwordField;

@property (retain, nonatomic) IBOutlet UITextField *confirmPassword;

@property (weak, nonatomic) IBOutlet UIButton *registerBtn;
@property (weak, nonatomic) IBOutlet UITextField *FirstName;
@property (weak, nonatomic) IBOutlet UITextField *LastName;

@property (weak, nonatomic) IBOutlet UITextField *Age;

@property (weak, nonatomic) IBOutlet UITextField *AccountType;

- (IBAction)RegisterUser:(id)sender;
@property (strong, nonatomic) IBOutlet UILabel *status;

- (IBAction)BackgroundTouch:(id)sender;

@end

