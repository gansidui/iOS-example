//
//  UserAddViewController.m
//  Hello
//
//  Created by dackli on 16/5/10.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "UserAddViewController.h"

@interface UserAddViewController ()

@property (weak, nonatomic) IBOutlet UITextField *openIdTextField;

@end

@implementation UserAddViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    static BOOL bShowed = NO;
    if (!bShowed) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"注意" message:@"identifier相当于账号" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *action = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil];
        [alert addAction:action];
        [self presentViewController:alert animated:YES completion:nil];
        
        bShowed = YES;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addUser:(id)sender {
    if (_openIdTextField.text.length == 0) {
        return;
    }
    
    if (_delegate) {
        [_delegate userSelected:_openIdTextField.text];
    }
    [self.navigationController popViewControllerAnimated:YES];
}

@end
