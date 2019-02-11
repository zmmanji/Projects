//
//  CircleShapeLayer.h
//  CircularProgressControl
//
//  Created by Christy Tao on 22/11/15.
//  Copyright (c) 2015 Addled. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface CircleShapeLayer : CAShapeLayer

@property (nonatomic) NSTimeInterval elapsedTime;
@property (nonatomic) NSTimeInterval timeLimit;
@property (assign, nonatomic, readonly) double percent;
@property (nonatomic) UIColor *progressColor;

@end
