//
//  UserSelectViewController.h
//  Hello
//
//  Created by dackli on 16/5/9.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol UserSelectViewControllerDelegate <NSObject>

- (void)userSelected:(NSString *)openId;

@end

@interface UserSelectViewController : UITableViewController

@property (nonatomic, assign) id<UserSelectViewControllerDelegate> delegate;

@end
