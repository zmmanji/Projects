//
//  UserInformation.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 08/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UserInformation : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *FirstName;
@property (weak, nonatomic) IBOutlet UILabel *LastName;
@property (weak, nonatomic) IBOutlet UILabel *Age;
@property (weak, nonatomic) IBOutlet UILabel *Username;
@property (weak, nonatomic) IBOutlet UITextField *Password;
@property (weak, nonatomic) IBOutlet UIButton *Logout;
- (IBAction)Logout:(id)sender;
@property (weak, nonatomic) IBOutlet UILabel *AccountType;
- (IBAction)Home:(id)sender;
@property (weak, nonatomic) IBOutlet UIButton *Home;

@end
