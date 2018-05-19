#ifndef TXVideoEditerTypeDef_H
#define TXVideoEditerTypeDef_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
/*
 * 视频信息
 */
@interface TXVideoInfo : NSObject
@property (nonatomic, strong) UIImage*              coverImage;     //视频首帧图片
@property (nonatomic, assign) CGFloat               duration;       //视频时长(s)
@property (nonatomic, assign) unsigned long long    fileSize;       //视频大小(byte)
@property (nonatomic, assign) int                   fps;            //视频fps
@property (nonatomic, assign) int                   bitrate;        //视频码率 (kbps)
@property (nonatomic, assign) int                   audioSampleRate;//音频采样率
@property (nonatomic, assign) int                   width;          //视频宽度
@property (nonatomic, assign) int                   height;         //视频高度
@property (nonatomic, assign) int                   angle;          //视频旋转角度
@end


/*
 * 短视频预览参数
 */
typedef NS_ENUM(NSInteger, TXPreviewRenderMode)
{
    PREVIEW_RENDER_MODE_FILL_SCREEN                 = 0,            //填充模式，尽可能充满屏幕不留黑边，所以可能会裁剪掉一部分画面
    PREVIEW_RENDER_MODE_FILL_EDGE                   = 1,            //黑边模式，尽可能保持画面完整，但当宽高比不合适时会有黑边出现
};

/*
 * 短视频预览参数
 */
@interface TXPreviewParam : NSObject
@property (nonatomic, strong) UIView*               videoView;      //视频预览View
@property (nonatomic, assign) TXPreviewRenderMode   renderMode;     //填充模式

@end


///////////////////////////////////////////////////////////////////////////////////
/*
 * 字幕
 */
@interface TXSubtitle: NSObject
@property (nonatomic, strong) UIImage*              titleImage;     //字幕图片   （这里需要客户把承载文字的控件转成image图片）
@property (nonatomic, assign) CGRect                frame;          //字幕的frame（注意这里的frame坐标是相对于渲染view的坐标）
@property (nonatomic, assign) CGFloat               startTime;      //字幕起始时间(s)
@property (nonatomic, assign) CGFloat               endTime;        //字幕结束时间(s)
@end

//////////////////////////////////////////////////////////////////////////////////////

/*
 * 生成视频结果错误码定义
 */
typedef NS_ENUM(NSInteger, TXGenerateResultCode)
{
    GENERATE_RESULT_OK                                   = 0,       //生成视频成功
    GENERATE_RESULT_FAILED                               = -1,      //生成视频失败
    GENERATE_RESULT_CANCEL                               = -2,      //生成视频取消
};

/*
 * 生成视频结果
 */
@interface TXGenerateResult : NSObject
@property (nonatomic, assign) TXGenerateResultCode  retCode;        //错误码
@property (nonatomic, strong) NSString*             descMsg;        //错误描述信息
@end

/*
 * 视频合成结果错误码定义
 */
typedef NS_ENUM(NSInteger, TXJoinerResultCode)
{
    JOINER_RESULT_OK                                = 0,            //合成成功
    JOINER_RESULT_FAILED                            = -1,           //合成失败
};
/*
 * 短视频合成结果
 */
@interface TXJoinerResult : NSObject
@property (nonatomic, assign) TXJoinerResultCode    retCode;         //错误码
@property (nonatomic, strong) NSString*             descMsg;         //错误描述信息

/*
 * 短视频压缩质量
 * 注意如果视频的分辨率小于压缩到的目标分辨率，视频不会被压缩，会保留原画
 */
typedef NS_ENUM(NSInteger, TXVideoCompressed)
{
    VIDEO_COMPRESSED_480P                              = 0,  //压缩至480P分辨率
    VIDEO_COMPRESSED_540P                              = 1,  //压缩至540P分辨率
    VIDEO_COMPRESSED_720P                              = 2,  //压缩至720P分辨率
};

@end

#endif
