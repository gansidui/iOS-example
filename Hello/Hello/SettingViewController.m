//
//  SettingViewController.m
//  Hello
//
//  Created by dackli on 16/5/11.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "SettingViewController.h"

@interface SettingViewController ()

@property (strong, nonatomic) IBOutlet UITableView *settingTableView;
@property (weak, nonatomic) IBOutlet UISwitch *testSwitch;
@property (weak, nonatomic) IBOutlet UISegmentedControl *segType;
@property (weak, nonatomic) IBOutlet UITableViewCell *authAudioSend;
@property (weak, nonatomic) IBOutlet UITableViewCell *authAudioRecv;
@property (weak, nonatomic) IBOutlet UITableViewCell *authVideoSend;
@property (weak, nonatomic) IBOutlet UITableViewCell *authVideoRecv;

@end

@implementation SettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [_testSwitch setOn:YES];
    [_segType setSelectedSegmentIndex:1];
    _authAudioSend.accessoryType = UITableViewCellAccessoryCheckmark;
    _authAudioRecv.accessoryType = UITableViewCellAccessoryNone;
    _authVideoSend.accessoryType = UITableViewCellAccessoryNone;
    _authAudioRecv.accessoryType = UITableViewCellAccessoryCheckmark;
    
    [_segType addTarget:self action:@selector(segTypeChanged:) forControlEvents:UIControlEventValueChanged];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (IBAction)segTypeChanged:(id)sender {
    
}

- (IBAction)testSwitchChanged:(id)sender {
}

- (IBAction)save:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)reset:(id)sender {
    // ...
    [self.navigationController popViewControllerAnimated:YES];
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (2 == indexPath.section) {
        UITableViewCell *selectedCell = [tableView cellForRowAtIndexPath:indexPath];
        if (selectedCell.accessoryType == UITableViewCellAccessoryCheckmark) {
            selectedCell.accessoryType = UITableViewCellAccessoryNone;
        }
        else {
            selectedCell.accessoryType = UITableViewCellAccessoryCheckmark;
        }
        
        if (0 == indexPath.row) {
            
        }
        else if (1 == indexPath.row) {
            
        }
        // ...
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 43.0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *sectionTitle = nil;
    if (2 == section) {
        sectionTitle = @"进房间权限";
    }
    return sectionTitle;
}

@end
