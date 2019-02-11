//
//  Session.m
//  CircularProgressControl
//
//  Created by Christy Tao on 22/11/15.
//  Copyright (c) 2015 Addled. All rights reserved.
//

#import "Session.h"

@implementation Session

- (NSTimeInterval)progressTime {
    
    if (_finishDate) {
        return [_finishDate timeIntervalSinceDate:self.startDate];
    }
    else {
        return [[NSDate date] timeIntervalSinceDate:self.startDate];
    }
}

@end
