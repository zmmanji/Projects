//
//  Accelerometer.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 21/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
@class CircleProgressView;
double currentaccx;
double currentaccy;
double currentaccz;
double currentrotx;
double currentroty;
double currentrotz;
double count;
double count2;
double count3;// for bicep
float count4; // for arm rotation
int number;
float i=1;


@interface Accelerometer : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *accx;
- (IBAction)demo:(id)sender;
@property (weak, nonatomic) IBOutlet UILabel *accy;
@property (weak, nonatomic) IBOutlet UILabel *accz;
@property (weak, nonatomic) IBOutlet UILabel *count4;
@property (weak, nonatomic) IBOutlet UILabel *status2;

@property (weak, nonatomic) IBOutlet UILabel *rotx;
@property (weak, nonatomic) IBOutlet UILabel *roty;
@property (weak, nonatomic) IBOutlet UILabel *rotz;
@property (weak, nonatomic) IBOutlet UIButton *Finish2;
@property (weak, nonatomic) IBOutlet UIButton *Back2;
- (IBAction)Finish2:(id)sender;
- (IBAction)Back2:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *Target;
@property (weak, nonatomic) IBOutlet UILabel *TargetLabel;

@property (weak, nonatomic) IBOutlet UILabel *maxx;

@property (weak, nonatomic) IBOutlet UILabel *maxy;
@property (weak, nonatomic) IBOutlet UILabel *ADD;

@property (weak, nonatomic) IBOutlet UILabel *maxz;
@property (weak, nonatomic) IBOutlet UILabel *maxrotationx;
@property (weak, nonatomic) IBOutlet UILabel *maxrotationy;
@property (weak, nonatomic) IBOutlet UILabel *maxrotationz;
@property (weak, nonatomic) IBOutlet UILabel *count;
- (IBAction)start:(id)sender;
@property (weak, nonatomic) IBOutlet UILabel *count2;
@property (weak, nonatomic) IBOutlet UIButton *NextScreen;
- (IBAction)NextScreen:(id)sender;
- (IBAction)Finish:(id)sender;
- (IBAction)back:(id)sender;
- (IBAction)actionButtonClick:(id)sender;





@property (weak, nonatomic) IBOutlet UILabel *status;
@property (weak, nonatomic) IBOutlet UILabel *bicep;

@property (strong, nonatomic) CMMotionManager *motionManager;
@property (weak, nonatomic) IBOutlet UIProgressView *Progress;

@property (strong, nonatomic) IBOutlet CircleProgressView *circleProgressView;

@property (weak, nonatomic) IBOutlet UIButton *actionButton;



- (IBAction)Reset:(id)sender;
- (IBAction)reset2:(id)sender;

@end
