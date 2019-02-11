//
//  HomePage.m
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 08/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

#import "HomePage.h"


@interface HomePage ()

@end

@implementation HomePage

- (void)viewDidLoad {
    NSUserDefaults * defaults= [NSUserDefaults standardUserDefaults];
    [super viewDidLoad];
     self.view.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
    _FirstName.text=[defaults objectForKey :@"FirstName"];
   
    
   
   /* if (count2>=5)
    {
        _ProgressHome.progress=1.0;
        
    }
    else if ((count2>=1)&&(count2<=4))
    {
        _ProgressHome.progress=0.5;
        
    }
    else
    {
        _ProgressHome.progress=0.0;
        
    }*/
    
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
    [self performSegueWithIdentifier:@"Login1" sender:self];
}

- (IBAction)ProfileView:(id)sender {
   
    [self performSegueWithIdentifier:@"Profile" sender:self];
}
- (IBAction)HandRotation:(id)sender {
    [self performSegueWithIdentifier:@"EX1" sender:self];
}

- (IBAction)BICEP:(id)sender {
    [self performSegueWithIdentifier:@"curl" sender:self];
}
- (IBAction)stats:(id)sender {
    [self performSegueWithIdentifier:@"ACC11" sender:self];
}
@end
