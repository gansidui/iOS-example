//
//  TXVodPlayer.h
//  TXLiteAVSDK
//
//  Created by annidyfeng on 2017/9/12.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TXLivePlayListener.h"
#import "TXVodPlayConfig.h"
#import "TXVideoCustomProcessDelegate.h"

@interface TXVodPlayer : NSObject

@property(nonatomic, weak) id <TXLivePlayListener> delegate;

@property(nonatomic, weak) id <TXVideoCustomProcessDelegate> videoProcessDelegate;

@property(nonatomic, assign) BOOL enableHWAcceleration;

@property(nonatomic, copy) TXVodPlayConfig *config;

@property BOOL isAutoPlay;  /// startPlay后是否立即播放，默认YES

/* setupContainView 创建Video渲染View,该控件承载着视频内容的展示。
 * 参数:
 *      view  : 父view
 *      idx   : Widget在父view上的层级位置
 */
- (void)setupVideoWidget:(UIView *)view insertIndex:(unsigned int)idx;

/* removeVideoView 移除Video渲染View
 */
- (void)removeVideoWidget;

/* startPlay 启动从指定URL播放RTMP音视频流
 * 参数:
 *      url : 完整的URL(如果播放的是本地视频文件，这里传本地视频文件的完整路径)
 * 返回: 0 = OK
 */
- (int)startPlay:(NSString *)url;

/* stopPlay 停止播放音视频流
 * 返回: 0 = OK
 */
- (int)stopPlay;

/* isPlaying 是否正在播放
 * 返回： YES 拉流中，NO 没有拉流
 */
- (bool)isPlaying;

/* pause 暂停播放
 *
 */
- (void)pause;

/* resume 继续播放
 *
 */
- (void)resume;

/*
 seek 播放跳转到音视频流某个时间
 * time: 流时间，单位为秒
 * 返回: 0 = OK
 */
- (int)seek:(float)time;


/*
 * setRenderRotation 设置画面的方向
 * 参数：
 *       rotation : 详见 TX_Enum_Type_HomeOrientation 的定义.
 */
- (void)setRenderRotation:(int)rotation;

/* setRenderMode 设置画面的裁剪模式
 * 参数
 *       renderMode : 详见 TX_Enum_Type_RenderMode 的定义。
 */
- (void)setRenderMode:(int)renderMode;


/**
 * 设置静音
 */
- (void)setMute:(BOOL)bEnable;

/*
 * 截屏
 * 参  数：
 *       snapshotCompletionBlock 通过回调返回当前图像
 * 返回值：
 */
- (void)snapshot:(void (^)(UIImage *))snapshotCompletionBlock;

/**
 * 设置播放速率
 *
 * 参  数：
 *       rate 正常速度为1.0；小于为慢速；大于为快速。最大建议不超过2.0
 *
 */
- (void)setRate:(float)rate;
@end
