//
//  UserInformation.m
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 08/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import "UserInformation.h"

@interface UserInformation ()

@end

@implementation UserInformation

- (void)viewDidLoad {
     NSUserDefaults * defaults= [NSUserDefaults standardUserDefaults];
    [super viewDidLoad];
    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    _FirstName.text=[defaults objectForKey :@"FirstName"];
    _LastName.text=[defaults objectForKey :@"LastName"];
    _Age.text=[defaults objectForKey :@"Age"];
    _Username.text=[defaults objectForKey :@"Username"];
    _Password.text=[defaults objectForKey :@"Password"];
    _AccountType.text=[defaults objectForKey :@"AccountType"];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)Logout:(id)sender {
    NSUserDefaults * defaults= [NSUserDefaults standardUserDefaults];

    [defaults setObject: _Password.text forKey:@"Password"];
   
    [self performSegueWithIdentifier:@"Return" sender:self];
}
- (IBAction)Home:(id)sender {
    NSString*A;
    A=@"PA";
    if ([_AccountType.text isEqualToString:(A)])
    {
     [self performSegueWithIdentifier:@"HOME12" sender:self];
    }
    else
    {
        [self performSegueWithIdentifier:@"HOME14" sender:self];
        
    }
}
@end
