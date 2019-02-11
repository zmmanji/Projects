//
//  Accelerometer.m
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 21/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import "Accelerometer.h"
#import "CircleProgressView.h"
#import "Session.h"
#import <CoreMotion/CoreMotion.h>



#define degrees(x) (180  * x / M_PI)

@interface Accelerometer ()
@property (strong, nonatomic) NSTimer *timer;
@property (nonatomic) Session *session;
@end

@implementation Accelerometer

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithRed:51/255.0 green:73/255.0 blue:93/255.0 alpha:1.0];
    
    self.session = [[Session alloc] init];
    self.session.state = kSessionStateStop;
    
    self.circleProgressView.status = NSLocalizedString(@"circle-progress-view.status-not-started", nil);
    self.circleProgressView.timeLimit = 60;
    self.circleProgressView.elapsedTime = 0;
    
    [self.actionButton setTintColor:[UIColor whiteColor]];
    
    [self startTimer];

    self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    // Do any additional setup after loading the view.
    count=0;
    count2=0;
    count3=0;
    number=0;
    currentaccx= 0;
    currentaccy= 0;
    currentaccz = 0;
    
    currentrotx= 0;
    currentroty = 0;
    currentrotz= 0;

    
    self.motionManager = [[CMMotionManager alloc] init];
    self.motionManager.accelerometerUpdateInterval = 0.18;
    self.motionManager.gyroUpdateInterval = 0.18;
    
    [self.motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue]
                                             withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
                                                 [self outputAccelertionData:accelerometerData.acceleration];
                                                 if(error){
                                                     
                                                     NSLog(@"%@", error);
                                                 }
                                             }];
    
    [self.motionManager startGyroUpdatesToQueue:[NSOperationQueue currentQueue]
                                    withHandler:^(CMGyroData *gyroData, NSError *error) {
                                        [self outputRotationData:gyroData.rotationRate];
                                    }];
    
  
    
    
}

- (void)viewDidDisappear:(BOOL)animated {
    [self.timer invalidate];
}
#pragma mark - Timer

- (void)startTimer {
    if ((!self.timer) || (![self.timer isValid])) {
        
        self.timer = [NSTimer scheduledTimerWithTimeInterval:1.00
                                                      target:self
                                                    selector:@selector(poolTimer)
                                                    userInfo:nil
                                                     repeats:YES];
    }
}

- (void)poolTimer
{
    if ((self.session) && (self.session.state == kSessionStateStart))
    {
        self.circleProgressView.elapsedTime = self.session.progressTime;
    }
}


#pragma mark - User Interaction

- (IBAction)actionButtonClick:(id)sender {
    
    if (self.session.state == kSessionStateStop) {
        
        self.session.startDate = [NSDate date];
        self.session.finishDate = nil;
        self.session.state = kSessionStateStart;
        
        UIColor *tintColor = [UIColor colorWithRed:184/255.0 green:233/255.0 blue:134/255.0 alpha:1.0];
        self.circleProgressView.status = NSLocalizedString(@"In-progress", nil);
        self.circleProgressView.tintColor = tintColor;
        self.circleProgressView.elapsedTime = 0;
        
        
    }
    else {
        self.session.finishDate = [NSDate date];
        self.session.state = kSessionStateStop;
        
        
        self.circleProgressView.status = NSLocalizedString(@"Paused", nil);
        self.circleProgressView.tintColor = [UIColor whiteColor];
        self.circleProgressView.elapsedTime = self.session.progressTime;
        
     
        
        [self.actionButton setTitle:NSLocalizedString(@"Start", nil) forState:UIControlStateNormal];
        [self.actionButton setTintColor:[UIColor whiteColor]];
    }
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void)outputAccelertionData:(CMAcceleration)acceleration
{
    
    
    
    self.accx.text = [NSString stringWithFormat:@" %.2fg",acceleration.x];
    if(fabs(acceleration.x) > fabs(currentaccx))
    {
        currentaccx = acceleration.x;
    }
    self.accy.text = [NSString stringWithFormat:@" %.2fg",acceleration.y];
    if(fabs(acceleration.y) > fabs(currentaccy))
    {
        currentaccy = acceleration.y;
    }
    self.accz.text = [NSString stringWithFormat:@" %.2fg",acceleration.z];
    if(fabs(acceleration.z) > fabs(currentaccz))
    {
        currentaccz = acceleration.z;
    }
    
    self.maxx.text = [NSString stringWithFormat:@" %.2f",currentaccx];
    self.maxy.text = [NSString stringWithFormat:@" %.2f",currentaccy];
    self.maxz.text = [NSString stringWithFormat:@" %.2f",currentaccz];
    
    
    
}

-(void)outputRotationData:(CMRotationRate)rotation
{
    
    self.rotx.text = [NSString stringWithFormat:@" %.2fr/s",degrees(rotation.x)];
    if(fabs(rotation.x) > fabs(currentrotx))
    {
        currentrotx = rotation.x;
    }
    self.roty.text = [NSString stringWithFormat:@" %.2fr/s",degrees(rotation.y)];
    if(fabs(rotation.y) > fabs(currentroty))
    {
        currentroty = rotation.y;
    }
    self.rotz.text = [NSString stringWithFormat:@" %.2fr/s",degrees(rotation.z)];
    if(fabs(rotation.z) > fabs(currentrotz))
    {
        currentrotz =rotation.z;
    }
    
    self.maxrotationx.text = [NSString stringWithFormat:@" %.2f",degrees(currentrotx)];
    self.maxrotationy.text = [NSString stringWithFormat:@" %.2f",degrees(currentroty)];
    self.maxrotationz.text = [NSString stringWithFormat:@" %.2f",degrees(currentrotz)];
    
   
    if (currentroty> (4.4))
    {
        NSLog(@"Counting :) ");
        
         currentroty=0;
        self.maxrotationy.text = [NSString stringWithFormat:@" %.2f",currentroty];
        float a= ((1.0)/(i));
        count4=count4+a;
        
       // count4=count4-number;
        self.count4.text = [NSString stringWithFormat:@" %.2f",count4];
        

    }
    else
    {
        self.count4.text = [NSString stringWithFormat:@" %.2f",count4];
        
    }
    
     self.count4.text = [NSString stringWithFormat:@" %.2f",count4];
    NSString *string=self.Target.text;
    double d;
    d=count4;
    NSString*I;
    I=[NSString stringWithFormat:@" %.2f",d];
    double doubleVal = [_Target.text doubleValue];
    NSString*U;
    U=[NSString stringWithFormat:@" %.2f",doubleVal];
    if (I==U)
    {
        _status2.text=@"Complete";
        
    }
    else
    {
        _status2.text=@"In Progress";
    }
    
    
    
    if ((currentrotx)<-4.40)//3.40
    {
        NSLog(@"Counted :)");
        currentrotx=0;
        self.maxrotationx.text = [NSString stringWithFormat:@" %.2f",currentrotx];

        count=count+1;
    }
  /*  else if (count>5)
    {
        double a;
        a=count-5;
        count=count-a;
        
    }*/
    
    
    self.count.text = [NSString stringWithFormat:@" %.2f",count];
    self.count2.text = [NSString stringWithFormat:@" %.2f",count];
    double b;
    b=5.00;
    NSString*B;
    B=[NSString stringWithFormat:@" %.2f",b];
    count2=count;
    
   /* if ([_count2.text isEqualToString:(B)])
    {
        _status.text=@"COMPLETE";
    }*/
    
    if (count2>=5)
    {
        _Progress.progress=1.0;
       _status.text=@"COMPLETE";
    }
    else if ((count2>1)&&(count2<=4))
    {
        _Progress.progress=0.8;
        _status.text=@"IN PROGRESS";
    }
    else
    {
        _Progress.progress=0.0;
        _status.text=@"NOT YET STARTED";
    }
   
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)Reset:(id)sender {
    currentaccx = 0;
    currentaccy = 0;
    currentaccz = 0;
    
    currentrotx= 0;
    currentroty= 0;
    currentrotz = 0;
    count=0;
    count3=0;
    
}

- (IBAction)reset2:(id)sender {
    currentaccx = 0;
    currentaccy = 0;
    currentaccz = 0;
    
    currentrotx= 0;
    currentroty= 0;
    currentrotz = 0;
    count=0;
    count3=0;
}
- (IBAction)start:(id)sender {
    double a;
    a=5.00;
    NSString*A;
    A=[NSString stringWithFormat:@" %.2f",a];
    NSLog(_count.text);
    NSLog(A);
   if ([_count.text isEqualToString:(A)])
   {
       UIAlertView *ALERT1 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU MADE IT :)") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
       [ALERT1 show];
       
   }
   else{
       UIAlertView *ALERT2 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU DIDNT MAKE IT :(") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
       [ALERT2 show];
       
   }
    
    
}
- (IBAction)NextScreen:(id)sender {
    [self performSegueWithIdentifier:@"HOME18" sender:self];
}

- (IBAction)Finish:(id)sender {
    double a;
    a=5.00;
    NSString*A;
    A=[NSString stringWithFormat:@" %.2f",a];
    NSLog(_count2.text);
    NSLog(A);
    if ([_count2.text isEqualToString:(A)])
    {
        UIAlertView *ALERT1 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU MADE IT :)") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [ALERT1 show];
        
    }
    else{
        UIAlertView *ALERT2 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU DIDNT MAKE IT :(") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [ALERT2 show];
        
    }

}
-(void) read
{
    CMAttitude*attitude;
    CMDeviceMotion *motion= _motionManager.deviceMotion;
    attitude=motion.attitude;
   // NSString* rotx=[NSString stringWithFormat:(@"X:,%f",)];
    
    
}

- (IBAction)back:(id)sender {
    i++;
   // currentaccx = 0;
   // currentaccy = 0;
   // currentaccz = 0;
    
   // currentrotx= 0;
   // currentroty= 0;
   // currentrotz = 0;
   // count=0;
   // count3=0;


    self.maxrotationx.text = [NSString stringWithFormat:@" %.2f",currentrotx];
    self.maxrotationy.text = [NSString stringWithFormat:@" %.2f",currentroty];
    self.maxrotationz.text = [NSString stringWithFormat:@" %.2f",currentrotz];
    [self performSegueWithIdentifier:@"HOME1" sender:self];
    
}






- (IBAction)Finish2:(id)sender {
    double d;
    d=count4;
    NSString*I;
    I=[NSString stringWithFormat:@" %.2f",d];
    double doubleVal = [_Target.text doubleValue];
    NSString*U;
    U=[NSString stringWithFormat:@" %.2f",doubleVal];
    if (I==U)
    {
        UIAlertView *ALERT1 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU MADE IT :)") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [ALERT1 show];
        
    }
    else{
        UIAlertView *ALERT2 =[[UIAlertView alloc] initWithTitle:(@"iPhsyio") message:(@"YOU DIDNT MAKE IT :(") delegate:(self) cancelButtonTitle:(@"OK") otherButtonTitles:nil];
        [ALERT2 show];
        
    }
}

- (IBAction)Back2:(id)sender {
    i++;
  //  number=number+1;
  //  currentaccx = 0;
  //  currentaccy = 0;
  //  currentaccz = 0;
    
  //  currentrotx= 0;
  //  currentroty= 0;
  //  currentrotz = 0;
     [self performSegueWithIdentifier:@"HOME111" sender:self];
    
}




- (IBAction)demo:(id)sender {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://youtu.be/Pt8qm40JfoY"]];
}

@end;
