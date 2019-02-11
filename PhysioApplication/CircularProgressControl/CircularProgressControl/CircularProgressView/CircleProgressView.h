//
//  CircleProgressView.h
//  CircularProgressControl
//
//  Created by Christy Tao on 22/11/15.
//  Copyright (c) 2015 Addled. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CircleProgressView : UIControl

@property (nonatomic) NSTimeInterval elapsedTime;

@property (nonatomic) NSTimeInterval timeLimit;

@property (nonatomic, retain) NSString *status;

@property (assign, nonatomic, readonly) double percent;

@end