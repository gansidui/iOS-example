//
//  TXUGCRecordClipManager.h
//  TXLiteAVSDK
//
//  Created by xiang zhang on 2017/8/25.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TXUGCPartsManager : NSObject
/**
 *  获取当前所有视频片段的总时长  单位：s
 */
-(float)getDuration;

/**
 *  获取所有视频片段路径
 */
-(NSArray *)getVideoPathList;

/**
 *  删除最后一段片段
 */
-(void)deleteLastPart;

/**
 *  删除指定片段
 */
-(void)deletePart:(int)index;

/**
 *  删除所有片段
 */
-(void)deleteAllParts;

@end
