//
//  ProgressViewController.h
//  CircularProgressControl
//
//  Created by Christy Tao on 22/11/15.
//  Copyright (c) 2015 Addled. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CircleProgressView;

@interface ProgressViewController : UIViewController

@property (strong, nonatomic) IBOutlet CircleProgressView *circleProgressView;

@property (strong, nonatomic) IBOutlet UIButton *actionButton;


@end