//
//  NLoginViewController.m
//  Hello
//
//  Created by dackli on 16/5/9.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "NLoginViewController.h"
#import "UserAddViewController.h"
#import "SettingViewController.h"

@interface NLoginViewController()

@property (nonatomic, strong) IBOutlet UITextField * textFieldRoomId;
@property (nonatomic, strong) IBOutlet UITextField * textFieldRoomRole;

@end


@implementation NLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (IBAction)setting:(id)sender {
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    SettingViewController *settingViewController = [storyboard instantiateViewControllerWithIdentifier:@"SettingViewController"];
    
    [self.navigationController pushViewController:settingViewController animated:YES];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    switch (section) {
        case 0: return 3;
        case 1: return 2;
        case 2: return 1;
    }
    return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (0 == section) {
        return @"账号";
    } else if (1 == section) {
        return @"房间";
    }
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (0 == indexPath.section) {
        if (0 == indexPath.row) {
            static UITableViewCell *cell = nil;
            if (!cell) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:@"cuUserId"];
            }
            cell.textLabel.text = @"当前账号";
            cell.detailTextLabel.text = @"123456";
            return cell;
        } else if (1 == indexPath.row) {
            static UITableViewCell *cell = nil;
            if (!cell) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseId"];
            }
            cell.textLabel.text = @"添加账号";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            return cell;
        } else if (2 == indexPath.row) {
            static UITableViewCell *cell = nil;
            if (!cell) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"deleteuseId"];
            }
            cell.textLabel.text = @"删除所有账号";
            cell.accessoryType = UITableViewCellAccessoryNone;
            return cell;
        }
        return nil;
    } else if (1 == indexPath.section) {
        if (0 == indexPath.row) {
            static UITableViewCell *cell = nil;
            if (!cell) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseId"];
                
                _textFieldRoomId = [[UITextField alloc] initWithFrame:CGRectMake(100, 0, 200, 40)];
                _textFieldRoomId.text = @"001";
                [cell.contentView addSubview:_textFieldRoomId];
                
                UILabel *textLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, 80, 40)];
                textLabel.text = @"房间号";
                [cell.contentView addSubview:textLabel];
                cell.selectionStyle = UITableViewCellSelectionStyleNone;
            }
            return cell;
        } else if (1 == indexPath.row) {
            static UITableViewCell *cell = nil;
            if (!cell) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseRole"];
                
                _textFieldRoomRole = [[UITextField alloc] initWithFrame:CGRectMake(120, 0, 200, 40)];
                _textFieldRoomRole.text = @"role1";
                [cell.contentView addSubview:_textFieldRoomRole];
                
                UILabel *textLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, 160, 40)];
                textLabel.text = @"流控角色名";
                [cell.contentView addSubview:textLabel];
                cell.selectionStyle = UITableViewCellSelectionStyleNone;
            }
            return cell;
        }
        return nil;
    } else {
        static UITableViewCell *cell = nil;
        if (!cell) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseId"];
        }
        cell.textLabel.text = @"进入";
        cell.textLabel.font = [UIFont boldSystemFontOfSize:16];
        cell.textLabel.textColor = [UIColor blueColor];
        return cell;
    }
    
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (0 == indexPath.section) {
        if (0 == indexPath.row) {
            UserSelectViewController *userSelectViewController = [[UserSelectViewController alloc] initWithStyle:UITableViewStyleGrouped];
            userSelectViewController.delegate = self;
            [self.navigationController pushViewController:userSelectViewController animated:YES];
            
        } else if (1 == indexPath.row) {
            UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
            UserSelectViewController *userAddViewController = [storyboard instantiateViewControllerWithIdentifier:@"UserAddViewController"];
            userAddViewController.delegate = self;
            [self.navigationController pushViewController:userAddViewController animated:YES];
            
        } else if (2 == indexPath.row) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"注意"
                                                                           message:@"继续操作会清除所有！！"
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleDefault
                                                           handler:^(UIAlertAction *action) {
                                                               
                                                           }];
            
            UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault
                                                                 handler:^(UIAlertAction *action) {
                                                                     
                                                                 }];
            
            [alert addAction:cancelAction];
            [alert addAction:okAction];

            [self presentViewController:alert animated:YES completion:nil];
        }
    }
}

#pragma mark - user selected delegate
- (void) userSelected:(NSString *)openId {
    
}


@end





