//
//  UserSelectViewController.m
//  Hello
//
//  Created by dackli on 16/5/9.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "UserSelectViewController.h"

@implementation UserSelectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"选择账号";
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 5; // test
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"reuseIdentifier"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseIdentifier"];
    }
    cell.accessoryType = UITableViewCellAccessoryNone;
    
    if (2 == indexPath.row) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }
    cell.textLabel.text = [[NSString alloc] initWithFormat:@"id_%ld", (long)indexPath.row];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *userId = [[NSString alloc] initWithFormat:@"id_%ld", (long)indexPath.row];
    if ([_delegate respondsToSelector:@selector(userSelected:)]) {
        [_delegate userSelected:userId];
    }
    
    [self dismissViewControllerAnimated:YES completion:nil];
    [self.tableView reloadData];
}

@end
