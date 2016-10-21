//
//  ChessBoardView.h
//  Gobang
//
//  Created by lijie on 2016/10/21.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import <UIKit/UIKit.h>

#define CHESS_TYPE_SPACE 0
#define CHESS_TYPE_BLACK 1
#define CHESS_TYPE_WHITE 2

@interface ChessBoardView : UIView

// 设置棋子，行数和列数都从1开始，[1,15][1,15]
- (void)setChess:(int)type withRow:(int)row withColumn:(int)column;

@end


@interface ChessManView : UIView

@property (nonatomic, assign) int type;
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;

- (id)initWithType:(int)type x:(int)x y:(int)y;

@end
