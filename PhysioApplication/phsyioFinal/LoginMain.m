//
//  LoginMain.m
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 07/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import "LoginMain.h"
#import "ViewController.h"


@interface LoginMain ()

@end

@implementation LoginMain
bool status1=false;

- (void)viewDidLoad {
    [super viewDidLoad];
     self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    
    NSString *docsDir;
    NSArray *dirPaths;
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    docsDir = [dirPaths objectAtIndex:0];
    databasePath = [[NSString alloc] initWithString: [docsDir stringByAppendingPathComponent: @"contacts.db"]];
    NSFileManager *filemgr = [NSFileManager defaultManager];



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

- (IBAction)Register:(id)sender {
    [self performSegueWithIdentifier:@"Back" sender:self];
}

- (IBAction)LoginUser:(id)sender {
    
    const char *dbpath = [databasePath UTF8String];
    sqlite3_stmt *statement;
    
    if (sqlite3_open(dbpath, &contactDB) == SQLITE_OK)
    {
        NSString *querySQL = [NSString stringWithFormat:@"SELECT address,phone from contacts where name=\"%@\"",_username.text];
        const char *query_stmt = [querySQL UTF8String];
        if (sqlite3_prepare_v2(contactDB, query_stmt, -1, &statement, NULL) == SQLITE_OK)
        {
            if (sqlite3_step(statement) == SQLITE_ROW)
            {
                NSString *passwordField1 = [[NSString alloc] initWithUTF8String:(const char *)sqlite3_column_text(statement, 0)];
                 //_password.text = passwordField1;
                NSLog(passwordField1);
                NSString *confirmPassword1 = [[NSString alloc] initWithUTF8String:(const char *)sqlite3_column_text(statement, 1    )];
               // confirmPassword.text = confirmPassword1;
                
               // status.text = @"已查到结果";
               
                   status1=true;
                NSString*A;
                A=self.password.text;
                if ([A isEqualToString:(passwordField1)])
                    
                {
                    status1=true;
                    UIAlertView *error =[[UIAlertView alloc] initWithTitle:(@"Physio Assist") message:(@"Welcome") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
                    [error show];
                    [self performSegueWithIdentifier:@"Home" sender:self];
                    NSLog(@"wELCOME ON BOARD");
                }

              
            }
            else {
                status.text = @"未查到结果";
                passwordField.text = @"";
                confirmPassword.text = @"";
            }
            sqlite3_finalize(statement);
        }
        
        sqlite3_close(contactDB);
    }
   
    
    
    
     NSUserDefaults * defaults= [NSUserDefaults standardUserDefaults];
     _AccountType.text=[defaults objectForKey :@"AccountType"];
    /*([_username.text isEqualToString: [defaults objectForKey :@"Username"]]&& [_password.text isEqualToString :[defaults objectForKey :@"Password"]]&&[_AccountType.text isEqualToString:@"PA"]&& status1==true)*/
    
    if (status==false)
    {
    if ([_username.text isEqualToString: [defaults objectForKey :@"Username"]]&& [_password.text isEqualToString :[defaults objectForKey :@"Password"]]&&[_AccountType.text isEqualToString:@"PA"]&& status1==true)
        
    {
    
    UIAlertView *error =[[UIAlertView alloc] initWithTitle:(@"Physio Assist") message:(@"Welcome") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [error show];
        [self performSegueWithIdentifier:@"Home" sender:self];
    }
    else if ([_username.text isEqualToString: [defaults objectForKey :@"Username"]]&& [_password.text isEqualToString :[defaults objectForKey :@"Password"]]&&[_AccountType.text isEqualToString:@"PY"])
    {
        UIAlertView *error =[[UIAlertView alloc] initWithTitle:(@"Welcome") message:(@"Welcome") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [error show];

        [self performSegueWithIdentifier:@"Physician" sender:self];
        
    }
    else
    {
        UIAlertView *fail =[[UIAlertView alloc] initWithTitle:(@"Login Credentials Failed") message:(@"Please Re-enter your username and password") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [ fail show];
        
    }

    }
    

}
@end
