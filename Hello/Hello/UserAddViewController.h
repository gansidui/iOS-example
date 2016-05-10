//
//  UserAddViewController.h
//  Hello
//
//  Created by dackli on 16/5/10.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UserSelectViewController.h"

@interface UserAddViewController : UITableViewController

@property (nonatomic, assign) id<UserSelectViewControllerDelegate> delegate;

@end
