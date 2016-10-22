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
    
    UIButton *restartButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    restartButton.frame = CGRectMake(40, CGRectGetMaxY(_chessBoardView.frame) + 60, 80, 80);
    [restartButton setTitle:@"新局" forState:UIControlStateNormal];
    [restartButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [restartButton addTarget:self action:@selector(restartButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:restartButton];
    
    UIButton *regretChessButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    regretChessButton.frame = CGRectMake(140, CGRectGetMaxY(_chessBoardView.frame) + 60, 80, 80);
    [regretChessButton setTitle:@"悔棋" forState:UIControlStateNormal];
    [regretChessButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [regretChessButton addTarget:self action:@selector(regretChessAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:regretChessButton];
    
    UIButton *aiButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    aiButton.frame = CGRectMake(240, CGRectGetMaxY(_chessBoardView.frame) + 60, 80, 80);
    [aiButton setTitle:@"AI" forState:UIControlStateNormal];
    [aiButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [aiButton addTarget:self action:@selector(aiButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:aiButton];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)restartButtonAction:(id)sender {
    [_chessBoardView restartChess];
}

- (void)regretChessAction:(id)sender {
    [_chessBoardView regretChess];
}

- (void)aiButtonAction:(id)sender {
    [_chessBoardView AI];
}

@end
