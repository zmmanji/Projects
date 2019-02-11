//
//  Physician.h
//  phsyioFinal
//
//  Created by Zeeshaan Manji on 09/11/2015.
//  Copyright © 2015 Zeeshaan Manji. All rights reserved.
//

//

//  Created by Christy on 09/11/2015.
//  Copyright © 2015 Christy. All rights reserved.

#import <UIKit/UIKit.h>

@interface Physician : UIViewController
@property (weak, nonatomic) IBOutlet UIButton *Logout;

- (IBAction)Logout:(id)sender;
- (IBAction)ProfileView:(id)sender;

@end
