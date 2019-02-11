//
//  ViewController.m
//  LoginUser
//
//  Created by Zeeshaan Manji on 06/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end


@implementation ViewController
@synthesize usernameField;
@synthesize passwordField;
@synthesize confirmPassword;
@synthesize status;

- (void)viewDidLoad {
    
    [super viewDidLoad];
    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    NSUserDefaults *defaults=[NSUserDefaults standardUserDefaults];
    if (![defaults boolForKey:@"registered"])
    {
        NSLog(@"No user is registered");
    }
    else
    {
        NSLog(@"User is Registered");
        confirmPassword.hidden=YES;
        _registerBtn.hidden=YES;
    }
    [self.usernameField resignFirstResponder];
    [self.view endEditing:TRUE];
    
    // Do any additional setup after loading the view, typically from a nib.
    CAGradientLayer *btnGradient = [CAGradientLayer layer];
    btnGradient.frame = _registerBtn.bounds;
    btnGradient.colors = [NSArray arrayWithObjects:
                          (id)[[UIColor colorWithRed:46.0f / 255.0f green:180.0f / 255.0f blue:213.0f / 255.0f alpha:1.0f] CGColor],
                          (id)[[UIColor colorWithRed:46.0f / 255.0f green:180.0f / 255.0f blue:213.0f / 255.0f alpha:1.0f] CGColor],
                          nil];
    [_registerBtn.layer insertSublayer:btnGradient atIndex:0];
    CALayer *btnLayer = [_registerBtn layer];
    [btnLayer setMasksToBounds:YES];
    [btnLayer setCornerRadius:5.0f];
    
    NSString *docsDir;
    NSArray *dirPaths;
    
    // Get the documents directory
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    docsDir = [dirPaths objectAtIndex:0];
    
    // Build the path to the database file
    databasePath = [[NSString alloc] initWithString: [docsDir stringByAppendingPathComponent: @"contacts.db"]];
    
    NSFileManager *filemgr = [NSFileManager defaultManager];
    
    if ([filemgr fileExistsAtPath:databasePath] == NO)
    {
        const char *dbpath = [databasePath UTF8String];
        if (sqlite3_open(dbpath, &contactDB)==SQLITE_OK)
        {
            char *errMsg;
            const char *sql_stmt = "CREATE TABLE IF NOT EXISTS CONTACTS(ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, ADDRESS TEXT,PHONE TEXT)";
            if (sqlite3_exec(contactDB, sql_stmt, NULL, NULL, &errMsg)!=SQLITE_OK) {
                status.text = @"创建表失败\n";
            }
        }
        else
        {
            status.text = @"创建/打开数据库失败";
        }
    }

    
}

-(IBAction) RegisterUser:(id)sender{
    sqlite3_stmt *statement;
    
    const char *dbpath = [databasePath UTF8String];
    
    if (sqlite3_open(dbpath, &contactDB)==SQLITE_OK) {
        NSString *insertSQL = [NSString stringWithFormat:@"INSERT INTO CONTACTS (name,address,phone) VALUES(\"%@\",\"%@\",\"%@\")",usernameField.text,passwordField.text,confirmPassword.text];
        const char *insert_stmt = [insertSQL UTF8String];
        sqlite3_prepare_v2(contactDB, insert_stmt, -1, &statement, NULL);
        if (sqlite3_step(statement)==SQLITE_DONE) {
            status.text = @"Registered ";
           // usernameField.text = @"";
           // passwordField.text = @"";
           // confirmPassword.text = @"";
        }
        else
        {
            status.text = @"Not Registered";
        }
        sqlite3_finalize(statement);
        sqlite3_close(contactDB);
    }

    if ([usernameField.text isEqualToString:@""] || [passwordField.text isEqualToString:@""] || [confirmPassword.text isEqualToString:@""] ||[_AccountType.text isEqualToString:@""])
    {
        UIAlertView *error =[[UIAlertView alloc] initWithTitle:(@"Login Error") message:(@"You must complete all the fields") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [error show];
    }
    else
    {
        [self CheckifPasswordMatch];
    }
}

- (IBAction)BackgroundTouch:(id)sender {
    
}



- (void) CheckifPasswordMatch
{
    if ([passwordField.text isEqualToString:confirmPassword.text])
    {
        NSLog(@"Passwords Match");
        [self Registernewuser];
    }
    else
    {
        UIAlertView *error =[[UIAlertView alloc] initWithTitle:(@"Login Error") message:(@"Passwords dont match,Please try again") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        
        
        
        [error show];
    }
    
}

-(void) Registernewuser
{
    NSUserDefaults * defaults= [NSUserDefaults standardUserDefaults];
    [defaults setObject: usernameField.text forKey:@"Username"];
    [defaults setObject: passwordField.text forKey:@"Password"];
    [defaults setObject: _FirstName.text forKey:@"FirstName"];
    [defaults setObject: _LastName.text forKey:@"LastName"];
    [defaults setObject: _Age.text forKey:@"Age"];
    [defaults setObject: _AccountType.text forKey:@"AccountType"];
    
    [self.view endEditing:TRUE];
    
    [defaults setBool:YES forKey:@"Registered"];
    
    
  
    UIAlertView *passed =[[UIAlertView alloc] initWithTitle:(@"Completed") message:(@"You have succesfully added a user") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
    
    [defaults synchronize];
    
    [ passed show];
    [self performSegueWithIdentifier:@"Login" sender:self];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
