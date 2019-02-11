//
//  Session.h
//  CircularProgressControl
//
//  Created by Christy Tao on 22/11/15.
//  Copyright (c) 2015 Addled. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    kSessionStateStart = 0,
    kSessionStateStop = 1
} SessionState;

@interface Session : NSObject

@property (nonatomic, retain) NSDate * startDate;
@property (nonatomic, retain) NSDate * finishDate;
@property (nonatomic, readonly) NSTimeInterval progressTime;
@property (nonatomic) SessionState state;

@end

