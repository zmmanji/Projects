//
//  HomePage.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 08/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HomePage : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *FirstName;
@property (weak, nonatomic) IBOutlet UIButton *Logout;
- (IBAction)Logout:(id)sender;
@property (strong, nonatomic) IBOutlet UIView *Navigation;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *Logout1;

@property (weak, nonatomic) IBOutlet UIButton *ProfileView;

- (IBAction)ProfileView:(id)sender;
@property (weak, nonatomic) IBOutlet UIButton *HandRotation;
- (IBAction)HandRotation:(id)sender;

@property (weak, nonatomic) IBOutlet UIButton *Bicep;

@property (weak, nonatomic) IBOutlet UIProgressView *ProgressHome;
- (IBAction)BICEP:(id)sender;

@property (weak, nonatomic) IBOutlet UIButton *Stats;
- (IBAction)stats:(id)sender;


 @end