//
//  TXUGCEdit.h
//  TXRTMPSDK
//
//  Created by xiang zhang on 2017/4/10.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>
#import "TXVideoEditerListener.h"
#import "TXVideoEditerTypeDef.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  UGC list /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoInfoReader : NSObject
/*
 * number 当前采样的是第几张图片（number 从1开始）
 * image  当前采样图片
 */
typedef void(^sampleProcess)(int number , UIImage * image);

/* 获取视频文件信息
 * videoPath 视频文件路径
 */
+ (TXVideoInfo *)getVideoInfo:(NSString *)videoPath;

/* 获取视频文件信息
 * asset 视频文件属性
 */
+ (TXVideoInfo *)getVideoInfoWithAsset:(AVAsset *)videoAsset;

/*获取视频的采样图列表
 *count         获取的采样图数量（均匀采样）
 *videoPath     视频文件路径
 *sampleProcess 采样进度
 */
+ (void)getSampleImages:(int)count
              videoPath:(NSString *)videoPath
               progress:(sampleProcess)sampleProcess;

/*获取视频的采样图列表
 *count         获取的采样图数量（均匀采样）
 *videoAsset   视频文件属性
 *sampleProcess 采样进度
 */
+ (void)getSampleImages:(int)count
             videoAsset:(AVAsset *)videoAsset
               progress:(sampleProcess)sampleProcess;

/**
 * 根据时间获取单帧图片
 * time 获取图片的时间
 * videoPath 视频文件路径
 */
+ (UIImage *)getSampleImage:(float)time
                  videoPath:(NSString *)videoPath;

/**
 * 根据时间获取单帧图片
 * time 获取图片的时间
 * videoAsset 视频文件属性
 */
+ (UIImage *)getSampleImage:(float)time
                 videoAsset:(AVAsset *)videoAsset;
@end


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  Video Edit //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoEditer : NSObject
@property (nonatomic ,weak) id<TXVideoGenerateListener> generateDelegate;
@property (nonatomic ,weak) id<TXVideoPreviewListener>  previewDelegate;

- (instancetype)initWithPreview:(TXPreviewParam *)param;

/*
 *videoPath:视频文件路径
 * 返回值：
 *       0 成功；
 *      -1 视频文件不存在；
 */
- (int)setVideoPath:(NSString *)videoPath;

/*
 *videoAsset:视频属性asset,从本地相册loading出来的视频，可以直接传入对应的视频属性，会极大的降低视频从相册loading的时间，具体请参考demo用法
 * 返回值：
 *       0 成功；
 *      -1 视频属性asset 为nil；
 */
- (int)setVideoAsset:(AVAsset *)videoAsset;


/*渲染某一时刻的视频画面
 *time      预览帧时间(s)
 */
- (void)previewAtTime:(CGFloat)time;

/*播放某一时间段的视频
 *startTime     播放起始时间(s)
 *endTime       播放结束时间(s)
 */
- (void)startPlayFromTime:(CGFloat)startTime
                   toTime:(CGFloat)endTime;

/*
 *暂停播放
 */
- (void)pausePlay;


/*继续播放
 */
- (void)resumePlay;

/*停止播放
 */
- (void)stopPlay;

/*
 *设置全局水印
 *waterMark            全局水印图片
 *normalizationFrame   水印相对于视频图像的归一化frame，x,y,width,height 取值范围 0~1；
                       height不用设置，sdk内部会根据水印宽高比自动计算height；
                       比如视频图像大小为（540，960） frame设置为（0.1，0.1，0.1,0）,水印的实际像素坐标为（540 * 0.1，960 * 0.1，540 * 0.1 ，540 * 0.1 * waterMark.size.height / waterMark.size.width）
 */
- (void) setWaterMark:(UIImage *)waterMark  normalizationFrame:(CGRect)normalizationFrame;

/*
 *设置片尾水印
 *tailWaterMark        片尾水印图片
 *normalizationFrame   水印相对于视频图像的归一化frame，x,y,width,height 取值范围 0~1；
                       height不用设置，sdk内部会根据水印宽高比自动计算height；
                       比如视频图像大小为（540，960） frame设置为（0.1，0.1，0.1,0）,水印的实际像素坐标为（540 * 0.1，960 * 0.1，540 * 0.1 ，540 * 0.1 * waterMark.size.height / waterMark.size.width）
 *duration             水印的持续时长
 */
- (void) setTailWaterMark:(UIImage *)tailWaterMark normalizationFrame:(CGRect)normalizationFrame duration:(CGFloat)duration;

/*
 *设置美颜，美白级别
 */

- (void) setBeautyFilter:(float)beautyLevel setWhiteningLevel:(float)whiteningLevel;

/*
 *设置特效滤镜
 */
- (void) setFilter:(UIImage *)image;

/*
 *设置视频加速播级别
 *level  1.0 ~ 4.0  1.0表示原速，4.0表示4倍加速
 */
- (void) setSpeedLevel:(float)level;

/*
 *设置背景音乐
 *path      音乐文件路径
 *result
 *       0 成功；
 *      -1 音乐文件格式不支持
 */
- (void) setBGM:(NSString *)path result:(void(^)(int))result;

/*
 *设置背景音乐的起始时间和结束时间
 *startTime 音乐起始时间
 *endTime   音乐结束时间
 */
- (void) setBGMStartTime:(float)startTime endTime:(float)endTime;

/*
 *设置视频声音大小
 *volume 0 ~ 1.0
 */
- (void) setVideoVolume:(float)volume;

/*
 *设置背景音乐声音大小  
 *volume 0 ~ 1.0
 */
- (void) setBGMVolume:(float)volume;

/*
 *设置字幕列表
 *subtitleList 字幕列表
 */
- (void) setSubtitleList:(NSArray<TXSubtitle *> *)subtitleList;


/*
 *设置视频剪裁
 *startTime 视频起始时间
 *endTime   视频结束时间
 */
- (void) setCutFromTime:(float)startTime toTime:(float)endTime;

/*
 *生成视频
 *优点：兼容性好，支持各种操作类型的视频生成，生成的视频文件在各个平台播放的兼容性好
 *缺点：生成视频速度稍慢
 *videoCompressed 视频压缩质量
 *videoOutputPath 视频操作之后存储路径
 *generateVideo 之后在TXVideoGenerateListener里面监听结果回调
 */
- (void) generateVideo:(TXVideoCompressed)videoCompressed videoOutputPath:(NSString *)videoOutputPath;

/*
 *使用系统函数快速生成视频
 *优点：生成视频速度快
 *缺点：1，剪切出来的视频在各个平台播放的兼容性稍差
       2，只有剪切和压缩操作才会使用系统函数，其他情况系统不支持，SDK内部会自动走正常视频生成的逻辑
 *videoCompressed 视频压缩质量
 *videoOutputPath 视频操作之后存储路径
 *quickGenerateVideo 之后在TXVideoGenerateListener里面监听结果回调
 */
- (void) quickGenerateVideo:(TXVideoCompressed)videoCompressed videoOutputPath:(NSString *)videoOutputPath;

/*
 *停止视频文件生成
 */
- (void) cancelGenerate;
@end

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  UGC Joiner //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoJoiner : NSObject
@property (nonatomic ,weak) id<TXVideoJoinerListener>  joinerDelegate;
@property (nonatomic ,weak) id<TXVideoPreviewListener> previewDelegate;

/*
 * param:参考 TXPreviewParam
 */
- (instancetype)initWithPreview:(TXPreviewParam *)param;

/*
 *videoPathList  :视频列表文件
 * 返回值：
 *       0 成功；
 *      -1 视频列表文件不存在；
*/
- (int)setVideoPathList:(NSArray *)videoPathList;

/*
 *videoAssetList:视频属性asset列表,从本地相册loading出视频列表后，可以直接传入对应的视频属性列表，会极大的降低视频从相册loading的时间，具体请参考demo用法
 * 返回值：
 *       0 成功；
 *      -1 视频属性asset列表不存在；
 */
- (int)setVideoAssetList:(NSArray<AVAsset *> *)videoAssetList;

/* 开启视频播放，会从视频的起始位置开始播放 （需要在setVideoPathList之后调用）
 */
- (void)startPlay;

/*暂停播放
 */
- (void)pausePlay;

/*继续播放
 */
- (void)resumePlay;

/*停止播放
 */
- (void)stopPlay;

/*合成视频
 *优点：合成出来的视频在各个平台播放的兼容性较好
 *缺点：合成速度稍慢
 *videoCompressed 视频压缩质量
 *videoOutputPath 生成新的视频存储路径
 *joinVideo之后在TXVideoComposeListener里面监听结果回调
 *提醒：需要合成的视频列表中，每个视频必须要有video data 和 audio data 数据
 */
- (void)joinVideo:(TXVideoCompressed)videoCompressed  videoOutputPath:(NSString *)videoOutputPath;

/*
 *使用系统函数快速合成视频
 *优点：合成速度快
 *缺点：合成出来的视频在各个平台播放的兼容性稍差
 *videoCompressed 视频压缩质量
 *videoOutputPath 视频操作之后存储路径
 *quickJoinVideo之后在TXVideoComposeListener里面监听结果回调
 *提醒：需要合成的视频列表中，每个视频必须要有video data 和 audio data 数据
 */
- (void)quickJoinVideo:(TXVideoCompressed)videoCompressed  videoOutputPath:(NSString *)videoOutputPath;

/*
 *停止视频文件合成
 */
- (void)cancelJoin;

@end



