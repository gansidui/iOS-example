//
//  ViewController.m
//  Gobang
//
//  Created by lijie on 2016/10/21.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "ViewController.h"
#import "ChessBoardView.h"

@interface ViewController ()
{
    ChessBoardView *_chessBoardView;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithRed:0.64 green:0.52 blue:0.38 alpha:1.0];
    _chessBoardView = [[ChessBoardView alloc] initWithFrame:CGRectMake(30, 100, 320, 320)];
    [self.view addSubview:_chessBoardView];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
