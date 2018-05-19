#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TXUGCRecordTypeDef.h"
#import "TXUGCRecordListener.h"
#import "TXUGCPartsManager.h"
#import "TXVideoCustomProcessDelegate.h"

/**********************************************
 **************  推流端短视频录制   **************
 **********************************************/

@interface TXUGCRecord : NSObject

@property (nonatomic, weak)   id<TXUGCRecordListener>   recordDelegate;

@property (nonatomic, weak)   id<TXVideoCustomProcessDelegate> videoProcessDelegate;

@property (nonatomic, strong, readonly) TXUGCPartsManager *partsManager; //视频片段管理


+ (TXUGCRecord*) shareInstance;

/*
 * 开始画面预览
 * 参  数：
 *       preview 预览画面的父view
 */
- (int) startCameraSimple:(TXUGCSimpleConfig*)config preview:(UIView *)preview;


/*
 * 开始画面预览
 * 参  数：
 *       preview 预览画面的父view
 */
- (int) startCameraCustom:(TXUGCCustomConfig*)config preview:(UIView *)preview;


/*
 * 设置视频录制比例：3：4  9：16  1：1
 */
- (void) setAspectRatio:(TXVideoAspectRatio)videoRatio;


/*
 设置录制速率
 * 参  数：
 *       rate 设置录制速率
 */
- (void) setRate:(CGFloat)rate;

/*
 * 结束画面预览
 */
- (void) stopCameraPreview;


/*
 * 开始录制短视频，SDK内部会自动生成视频路经，在TXVideoRecordListener里面返回
 * 返回值：
 *       0 成功；
 *      -1 正在录制短视频；
 *      -2 videoRecorder初始化失败；
*       -3 摄像头没有打开；
 *      -4 麦克风没有打开；
 */
- (int) startRecord;


/*
 * 开始录制短视频
 * 参  数：
 *       videoPath 视频文件输出路径
 *       coverPath 封面文件输出路径
 * 返回值：
 *       0 成功；
 *      -1 正在录制短视频；
 *      -2 videoRecorder初始化失败；
 *      -3 videoPath 为nil；
 */
- (int) startRecord:(NSString *)videoPath coverPath:(NSString *)coverPath;

/*
 * 暂停录制短视频(注:切后台时需保持后台运行状态)
 * 每一次暂停录制都会生成一个视频片段，您可以在partsManager里面管理这些视频片段
 * 返回值：
 *       0 成功；
 *      -1 不存在录制任务；
 *      -2 videoRecorder未初始化；
 */
- (int) pauseRecord;

/*
 * 恢复录制短视频
 * 返回值：
 *       0 成功；
 *      -1 不存在录制任务；
 *      -2 videoRecorder未初始化；
 */
- (int) resumeRecord;

/*
 * 结束录制短视频
 * 返回值：
 *       0 成功；
 *      -1 不存在录制任务；
 *      -2 videoRecorder未初始化；
 */
-(int) stopRecord;

#pragma mark ----Camera, Beauty, Filter----

/*
 *设置全局水印
 *waterMark            全局水印图片
 *normalizationFrame   水印相对于视频图像的归一化frame，x,y,width,height 取值范围 0~1；
                       height不用设置，sdk内部会根据水印宽高比自动计算height；
                       比如视频图像大小为（540，960） frame设置为（0.1，0.1，0.1,0）,水印的实际像素坐标为（540 * 0.1，960 * 0.1，540 * 0.1 ，540 * 0.1 * waterMark.size.height / waterMark.size.width）
 */
- (void) setWaterMark:(UIImage *)waterMark  normalizationFrame:(CGRect)normalizationFrame;

/* 各种情况下的横竖屏录制 参数设置
 //activity竖屏模式，竖屏录制
 [[TXUGCRecord shareInstance] setHomeOrientation:VIDEO_HOME_ORIENTATION_DOWN];
 [[TXUGCRecord shareInstance] setRenderRotation:0];
 
 //activity竖屏模式，home在右横屏录制
 [[TXUGCRecord shareInstance] setHomeOrientation:VIDOE_HOME_ORIENTATION_RIGHT];
 [[TXUGCRecord shareInstance] setRenderRotation:90];
 
 //activity竖屏模式，home在左横屏录制
 [[TXUGCRecord shareInstance] setHomeOrientation:VIDEO_HOME_ORIENTATION_LEFT];
 [[TXUGCRecord shareInstance] setRenderRotation:270];
 
 //activity横屏模式，home在右横屏录制 注意：渲染view要跟着activity旋转
 [[TXUGCRecord shareInstance] setHomeOrientation:VIDOE_HOME_ORIENTATION_RIGHT];
 [[TXUGCRecord shareInstance] setRenderRotation:0];
 
 //activity横屏模式，home在左横屏录制 注意：渲染view要跟着activity旋转
 [[TXUGCRecord shareInstance] setHomeOrientation:VIDEO_HOME_ORIENTATION_LEFT];
 [[TXUGCRecord shareInstance] setRenderRotation:0];
 */


/* home键所在方向，用来切换横竖屏录制（tips：此参数的设置可能会改变本地预览的方向，此参数设置后，请调用setRenderRotation 来修本地视预览频流方向，具体请参考demo设置 ）
 * 1,homeOrientation=VIDEO_HOME_ORIENTATION_DOWN  Home键在下竖屏推流
 * 2,homeOrientation=VIDOE_HOME_ORIENTATION_RIGHT Home键在右横屏推流
 * 3.homeOrientation=VIDEO_HOME_ORIENTATION_LEFT  Home键在左横屏推流
 */
- (void) setHomeOrientation:(TXVideoHomeOrientation)homeOrientation;

/*
 * setRenderRotation 设置预览视频方向
 * rotation : 取值为 0 , 90, 180, 270（其他值无效） 表示推流端预览视频向右旋转的角度
 * 注意：横竖录制,activty旋转可能会改变预览视频流方向，可以设置此参数让预览视频回到正方向，具体请参考demo设置，如果demo里面的设置满足不了您的业务需求，请自行setRenderRotation到自己想要的方向
 */
- (void) setRenderRotation:(int)rotation;

/* setBeautyLevel 设置美颜 和 美白 效果级别
 * 参数：
 *          beautyStyle     : 美颜风格，TX_Enum_Type_BeautyStyle类型。
 *          beautyLevel     : 美颜级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 *          whitenessLevel  : 美白级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 *          ruddinessLevel  : 红润级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setBeautyStyle:(int)beautyStyle beautyLevel:(float)beautyLevel whitenessLevel:(float)whitenessLevel ruddinessLevel:(float)ruddinessLevel;

/* setFilter 设置指定素材滤镜特效
 * 参数：
 *          image     : 指定素材，即颜色查找表图片。注意：一定要用png格式！！！
 *          demo用到的滤镜查找表图片位于RTMPiOSDemo/RTMPiOSDemo/resource／FilterResource.bundle中
 */
-(void) setFilter:(UIImage*)filterImage;

/* setSpecialRatio 设置滤镜效果程度
 * 参数：
 *          specialValue     : 从0到1，越大滤镜效果越明显，默认取值0.5
 */

-(void) setSpecialRatio:(float)specialRatio;

/* setEyeScaleLevel  设置大眼级别（涉及人脸识别,增值版本有效，普通版本设置此参数无效）
 * 参数：
 *          eyeScaleLevel     : 大眼级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
-(void) setEyeScaleLevel:(float)eyeScaleLevel;

/* setFaceScaleLevel  设置瘦脸级别（涉及人脸识别,增值版本有效，普通版本设置此参数无效）
 * 参数：
 *          faceScaleLevel    : 瘦脸级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
-(void) setFaceScaleLevel:(float)faceScaleLevel;

/* setFaceVLevel  设置V脸（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          faceVLevel    : V脸级别取值范围 0 ~ 9； 0 表示关闭 1 ~ 9值越大 效果越明显。
 */
- (void)setFaceVLevel:(float)faceVLevel;

/* setChinLevel  设置下巴拉伸或收缩（特权版本有效，普通版本设置此参数无效）
 * 参数：
 *          chinLevel    : 下巴拉伸或收缩取值范围 -9 ~ 9； 0 表示关闭 -9收缩 ~ 9拉伸。
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


/**
 * 设置绿幕文件
 *
 * @param file: 绿幕文件路径。支持mp4; nil 关闭绿幕
 */
-(void) setGreenScreenFile:(NSURL *)file;

/**
 * 选择动效 （涉及人脸识别,增值版本有效，普通版本设置此参数无效）
 *
 */
- (void) selectMotionTmpl:(NSString *)tmplName inDir:(NSString *)tmplDir;


/**
 * 设置背景音乐文件
 * @param path: 音乐文件路径，一定要是app对应的document目录下面的路径，否则文件会读取失败
 * return:
 *        音乐时长 s
 */
- (CGFloat) setBGM:(NSString *)path;

/*
 *播放背景音乐
 *@param startTime 音乐播放起始时间
 *@param endTime   音乐播放结束时间
 *@param beginNotify: 音乐播放开始的回调通知
 *@param progressNotify: 音乐播放的进度通知，单位毫秒
 *@param completeNotify: 音乐播放结束的回调通知
 */
- (BOOL)playBGMFromTime:(float)startTime
                 toTime:(float)endTime
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


/* setMicVolume 设置麦克风的音量大小，播放背景音乐混音时使用，用来控制麦克风音量大小
 * @param volume: 音量大小，1为正常音量，建议值为0~2，如果需要调大音量可以设置更大的值
 */
- (BOOL)setMicVolume:(float)volume;

/* setBGMVolume 设置背景音乐的音量大小，播放背景音乐混音时使用，用来控制背景音音量大小
 * @param volume: 音量大小，1为正常音量，建议值为0~2，如果需要调大背景音量可以设置更大的值
 */
- (BOOL)setBGMVolume:(float)volume;

/*
 * 切换前后摄像头
 * 参  数：
 *       isFront 是否前后摄像头
 * 返回：
 *      YES，切换成功。
 *      NO，切换失败。
 */
- (BOOL) switchCamera:(BOOL)isFront;


/* toggleTorch, 打开闪关灯。
 * 参数
 *          enable: YES, 打开    NO, 关闭.
 * 返回：
 *          YES，打开成功。
 *          NO，打开失败。
 */
- (BOOL) toggleTorch:(BOOL)enable;


/**
 * 调整焦距
 * 说明：distance取值范围 1~5 ，当为1的时候为最远视角（正常镜头），当为5的时候为最近视角（放大镜头），这里最大值推荐为5，超过5后视频数据会变得模糊不清
 */
- (void)setZoom:(CGFloat)distance;
@end
