//
//  MainTabViewController.m
//  HelloAV
//
//  Created by lijie on 2018/5/19.
//  Copyright © 2018年 Test. All rights reserved.
//

#import "MainTabViewController.h"
#import "VodListViewController.h"
#import "UserInfoViewController.h"

@interface MainTabViewController () <UITabBarControllerDelegate>

@end

@implementation MainTabViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setup];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setup {
    VodListViewController *vodListView = [[VodListViewController alloc] init];
    UserInfoViewController *userInfoView = [[UserInfoViewController alloc] init];
    
    self.viewControllers = @[vodListView, userInfoView];
    
    [self addChildViewController:vodListView imageName:@"video_normal" selectedImageName:@"video_click" title:nil];
    [self addChildViewController:userInfoView imageName:@"user_normal" selectedImageName:@"user_click" title:nil];
    
    self.delegate = self;
    [self setSelectedIndex:0];
}

- (void)addChildViewController:(UIViewController *)childController imageName:(NSString *)normalImg selectedImageName:(NSString *)selectImg title:(NSString *)title {
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:childController];
    nav.tabBarItem.image = [[UIImage imageNamed:normalImg] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    nav.tabBarItem.selectedImage = [[UIImage imageNamed:selectImg] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    nav.title = title;
    
    [self addChildViewController:nav];
}

- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController {
    return YES;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

@end
