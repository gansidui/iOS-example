//
//  VodListMode.h
//  HelloAV
//
//  Created by lijie on 2018/5/19.
//  Copyright © 2018年 Test. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VodInfo : NSObject

@property NSString *videoId;   // 视频id
@property NSString *title;     // 视频标题
@property NSString *cover;     // 视频封页图片链接
@property NSString *playUrl;   // 视频播放地址

@end


@interface VodListMgr : NSObject

// 服务器会根据videoId来返回对应的数据，比如为0表示返回最新的10组数据，为100，表示返回Id为[99,90]的数据
- (void)requestVideoList:(NSString *)videoId;

@end
