//
//  TXLivePush.h
//  LiteAV
//
//  Created by alderzhang on 2017/5/24.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>
#import <UIKit/UIKit.h>
#import <ReplayKit/ReplayKit.h>
#import "TXLivePushConfig.h"
#import "TXLivePushListener.h"
#import "TXVideoCustomProcessDelegate.h"

@interface TXLivePush : NSObject

@property(nonatomic, copy) TXLivePushConfig *config;

@property(nonatomic, weak) id <TXLivePushListener> delegate;

@property(nonatomic, weak) id <TXVideoCustomProcessDelegate> videoProcessDelegate;

// 当前推流URL
@property(nonatomic, readonly) NSString *rtmpURL;

// 当前是否为前置camera
@property(nonatomic, readonly) BOOL frontCamera;

// init 时候初始化config
- (id)initWithConfig:(TXLivePushConfig *)config;

/* startPush 启动到指定URL推流（rtmpURL 腾讯云的推流地址）
 * 参数:
 *      url : RTMP完整的URL
 bStartAudioCapture：表示是否由SDK启动音频采集；如果客户要自己负责音频采集，需要传入NO，然后：
 1. 通过setCustomAudioInfo将音频采样率、声道数、位宽通知给SDK，
 2. 再通过sendCustomPCMData发送音频数据，SDK只负责音频编码和音频数据的发送
 * 返回: 0 = OK
 */
- (int)startPush:(NSString *)rtmpURL;

/* stopPush 停止推流
 *
 */
- (void)stopPush;


/* 以下两个接口用于推默认数据及恢复推流，主要用于后台推流，具体使用方式请参考demo里面的示例
 * 当从前台切到后台的时候，调用pausePush会推配置里设置的图片(TXLivePushConfig.pauseImg)
 * 当从后台回到前台的时候，调用resumePush恢复推送camera采集的数据
 * @note 相关属性设置请参考TXLivePushConfig，
 * @property pauseImg：设置后台推流的默认图片，不设置为默认黑色背景
 * @property pauseFps：设置后台推流帧率，最小值为5，最大值为20，默认10
 * @property pauseTime：设置后台推流持续时长，单位秒，默认300秒
 */
//暂停推流，后台视频发送TXLivePushConfig里面设置的图像，音频发送静音
- (void)pausePush;

//恢复推流
- (void)resumePush;


/* isPublishing
 * 返回 YES 推流中，NO 没有推流
 */
- (bool)isPublishing;

/* startPreview 开始推流画面的预览。
 * 参数:
 *      view : 预览控件所在的父控件
 */
- (int)startPreview:(UIView *)view;

/* stopPreview 停止预览
 *
 */
- (void)stopPreview;

/* switchCamera 切换前后摄像头
 *
 */
- (int)switchCamera;

/* isMirror YES：播放端看到的是镜像画面   NO：播放端看到的是非镜像画面
 * (tips：推流端前置摄像头默认看到的是镜像画面，后置摄像头默认看到的是非镜像画面)
 */
- (void)setMirror:(BOOL)isMirror;


/* setBeautyLevel 设置美颜 和 美白 效果级别
 * 参数：
 
 *          beautyStyle     : TX_Enum_Type_BeautyStyle类型。
 *          beautyLevel     : 美颜级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 *          whitenessLevel  : 美白级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 *          ruddinessLevel  : 红润级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setBeautyStyle:(int)beautyStyle beautyLevel:(float)beautyLevel whitenessLevel:(float)whitenessLevel ruddinessLevel:(float)ruddinessLevel;

/* setEyeScaleLevel  设置大眼级别（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          eyeScaleLevel     : 大眼级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setEyeScaleLevel:(float)eyeScaleLevel;

/* setFaceScaleLevel  设置瘦脸级别（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          faceScaleLevel    : 瘦脸级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setFaceScaleLevel:(float)faceScaleLevel;

/* setFilter 设置指定素材滤镜特效
 * 参数：
 *          image     : 指定素材，即颜色查找表图片。注意：一定要用png格式！！！
 *          demo用到的滤镜查找表图片位于RTMPiOSDemo/RTMPiOSDemo/resource／FilterResource.bundle中
 */
- (void)setFilter:(UIImage *)image;

/* setSpecialRatio 设置滤镜效果程度
 * 参数：
 *          specialValue     : 从0到1，越大滤镜效果越明显，默认取值0.5
 */
- (void)setSpecialRatio:(float)specialValue;


/* setFaceVLevel  设置V脸（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          faceVLevel    : V脸级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setFaceVLevel:(float)faceVLevel;

/* setChinLevel  设置下巴拉伸或收缩（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          chinLevel    : 下巴拉伸或收缩级别取值范围 -9 ~ 9； 0 表示关闭 -9收缩 ~ 9拉伸。
 */
- (void)setChinLevel:(float)chinLevel;

/* setFaceShortLevel  设置短脸（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          faceShortlevel    : 短脸级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setFaceShortLevel:(float)faceShortlevel;

/* setNoseSlimLevel  设置瘦鼻（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          noseSlimLevel    : 瘦鼻级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setNoseSlimLevel:(float)noseSlimLevel;



/* toggleTorch, 打开闪关灯。
 * 参数
 *      YES, 打开，
 *      NO, 关闭.
 * 返回：
 *      YES，打开成功。
 *      NO，打开失败。
 */
- (BOOL)toggleTorch:(BOOL)bEnable;

/*
 * setRenderRotation 设置本地视频方向
 * rotation : 取值为 0 , 90, 180, 270（其他值无效） 表示推流端本地视频向右旋转的角度
 * 注意：横竖屏推流,activty旋转可能会改变本地视频流方向，可以设置此参数让本地视频回到正方向，具体请参考demo设置，如果demo里面的设置满足不了您的业务需求，请自行setRenderRotation到自己想要的方向（tips：推流端setRenderRotation不会改变观众端的视频方向）
 */
- (void)setRenderRotation:(int)rotation;


/**
 * 设置静音
 */
- (void)setMute:(BOOL)bEnable;

/**
 * 发送客户自定义的音频PCM数据
 * 说明：目前SDK只支持16位采样的PCM编码；如果是单声道，请保证传入的PCM长度为2048；如果是双声道，请保证传入的PCM长度为4096
 */
- (void)sendCustomPCMData:(unsigned char *)data len:(unsigned int)len;

/**
 * 发送自定义的SampleBuffer，代替sendCustomVideoData
 * 内部有简单的帧率控制，发太快会自动丢帧；超时则会重发最后一帧
 * @note 相关属性设置请参考TXLivePushConfig，autoSampleBufferSize优先级高于sampleBufferSize
 * @property sampleBufferSize，设置输出分辨率，如果此分辨率不等于sampleBuffer中数据分辨率则会对视频数据做缩放
 * @property autoSampleBufferSize，输出分辨率等于输入分辨率，即sampleBuffer中数据的实际分辨率
 */
- (void)sendVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 * Replaykit发送自定义音频包
 *  @prama sampleBuffer 声音
 *  @prama sampleBufferType     RPSampleBufferTypeAudioApp or RPSampleBufferTypeAudioMic,
 *
 *  当两种声音都发送时，内部做混音；否则只发送一路声音
 */
- (void)sendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

//TODO 未实现
/**
 * Replaykit发送静音包
 */
- (void)setSendAudioSampleBufferMuted:(BOOL)muted;

/**
 * 调用手动对焦功能
 * 说明:早期SDK版本手动对焦功能是由SDK内部触发，现在把手动对焦的接口开放出来，客户可以根据自己需求触发 ,如果客户调用这个接口，SDK内部触发对焦的逻辑将会停止，避免重复触发对焦逻辑
 * touchPoint为传入的对焦点位置
 */
- (void)setFocusPosition:(CGPoint)touchPoint;

/**
 * 调整焦距
 * 说明：distance取值范围 1~5 ，当为1的时候为最远视角（正常镜头），当为5的时候为最近视角（放大镜头），这里最大值推荐为5，超过5后视频数据会变得模糊不清
 */
- (void)setZoom:(CGFloat)distance;

//TODO 未实现
/* 以下接口用于混音处理，背景音与Mic采集到的人声混合
 * playBGM 播放背景音乐
 * @param path: 音乐文件路径，一定要是app对应的document目录下面的路径，否则文件会读取失败
 */
- (BOOL)playBGM:(NSString *)path;

/**
 * playBGM 播放背景音乐
 * @param path: 音乐文件路径，一定要是app对应的document目录下面的路径，否则文件会读取失败
 * @param beginNotify: 音乐播放开始的回调通知
 * @param progressNotify: 音乐播放的进度通知，单位毫秒
 * @param completeNotify: 音乐播放结束的回调通知
 */
- (BOOL)   playBGM:(NSString *)path
   withBeginNotify:(void (^)(NSInteger errCode))beginNotify
withProgressNotify:(void (^)(NSInteger progressMS, NSInteger durationMS))progressNotify
 andCompleteNotify:(void (^)(NSInteger errCode))completeNotify;

/**
 * 停止播放背景音乐
 */
- (BOOL)stopBGM;

/**
 * 暂停播放背景音乐
 */
- (BOOL)pauseBGM;

/**
 * 继续播放背景音乐
 */
- (BOOL)resumeBGM;

/**
 * 获取音乐文件总时长，单位毫秒
 * @param path: 音乐文件路径，如果path为空，那么返回当前正在播放的music时长
 */
- (int)getMusicDuration:(NSString *)path;

/* setMicVolume 设置麦克风的音量大小，播放背景音乐混音时使用，用来控制麦克风音量大小
 * @param volume: 音量大小，1为正常音量，建议值为0~2，如果需要调大音量可以设置更大的值
 */
- (BOOL)setMicVolume:(float)volume;

/* setBGMVolume 设置背景音乐的音量大小，播放背景音乐混音时使用，用来控制背景音音量大小
 * @param volume: 音量大小，1为正常音量，建议值为0~2，如果需要调大背景音量可以设置更大的值
 */
- (BOOL)setBGMVolume:(float)volume;

/**
 * setVideoQuality 设置视频质量
 * @param quality           : 画质类型(标清，高清，超高清)
 * @param adjustBitrate     : 动态码率开关
 * @param adjustResolution  : 动态切分辨率开关
 */
- (void)setVideoQuality:(TX_Enum_Type_VideoQuality)quality
          adjustBitrate:(BOOL) adjustBitrate
       adjustResolution:(BOOL) adjustResolution;

/* 设置混响效果
 * @param reverbType ：混响类型 ，详见 TXReverbType
 */
- (BOOL)setReverbType:(TXReverbType)reverbType;

/**
 * 设置绿幕文件。仅增值版有效
 *
 * @param file: 绿幕文件路径。支持mp4; nil 关闭绿幕
 */
- (void)setGreenScreenFile:(NSURL *)file;

/**
 * 选择动效。仅增值版有效
 *
 * @param tmplName: 动效名称
 * @param tmplDir: 动效所在目录
 */
- (void)selectMotionTmpl:(NSString *)tmplName inDir:(NSString *)tmplDir;

/**
 * 在渲染view上显示播放状态统计及事件消息浮层
 **/
- (void)showDebugLog:(BOOL)isShow;
@end
