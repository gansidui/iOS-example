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

- (void)restartChess;
- (void)regretChess;
- (void)AI;

@end


@interface ChessManView : UIView

@property (nonatomic, assign) char type;
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;

- (id)initWithType:(char)type x:(int)x y:(int)y;

@end
