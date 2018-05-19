//
//  VodListViewController.m
//  HelloAV
//
//  Created by lijie on 2018/5/19.
//  Copyright © 2018年 Test. All rights reserved.
//

#import "VodListViewController.h"
#import <MJRefresh/MJRefresh.h>

@interface VodListViewController () <UICollectionViewDelegate,UICollectionViewDataSource>

@end

@implementation VodListViewController
{
    NSMutableArray    *_videoList;
    UICollectionView  *_tableView;
    BOOL              *_isLoading;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    [layout setScrollDirection:UICollectionViewScrollDirectionVertical];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
