//
//  ViewController.m
//
//
//

//  Created by Christy on 09/11/2015.
//  Copyright © 2015 Christy. All rights reserved.


#import "ViewController.h"
#import "Physician.h"
#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>
@interface Physician ()<ABPeoplePickerNavigationControllerDelegate>
- (IBAction)Take:(id)sender;

@end

@implementation Physician

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)Take:(id)sender {
    ABPeoplePickerNavigationController *picker = [[ABPeoplePickerNavigationController alloc] init];
    picker.peoplePickerDelegate = self;
    // Display only a person's phone, email, and birthdate
    NSArray *displayedItems = [NSArray arrayWithObjects:[NSNumber numberWithInt:kABPersonPhoneProperty],
                               [NSNumber numberWithInt:kABPersonEmailProperty],
                               [NSNumber numberWithInt:kABPersonBirthdayProperty], nil];
    
    
    picker.displayedProperties = displayedItems;
    // Show the picker
    
    [self presentViewController:picker animated:YES completion:^{
        
    }];
    
}
- (IBAction)Logout:(id)sender {
    [self performSegueWithIdentifier:@"Home1" sender:self];
}

- (IBAction)ProfileView:(id)sender {
    [self performSegueWithIdentifier:@"Profile1" sender:self];
}
@end
