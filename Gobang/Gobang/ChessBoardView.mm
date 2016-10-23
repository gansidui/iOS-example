//
//  ChessBoardView.m
//  Gobang
//
//  Created by lijie on 2016/10/21.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "ChessBoardView.h"
#import "FiveChessAI.hpp"

#include <vector>

#define ROW_COUNT    (15)
#define COLUMN_COUNT (15)
#define CHESS_WIDTH  (20)
#define CHESS_HEIGHT (20)

@interface ChessBoardView()
{
    FiveChessAI  chessAI;
    char chessMap[ROW_COUNT][COLUMN_COUNT];
    std::vector<std::pair<int, int>> chessRecord;
}
@end

@implementation ChessBoardView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self clearChessMap];
    }
    return self;
}

- (void)drawRect:(CGRect)rect {
    [self drawBackground];
}

- (void)drawBackground {
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    [[UIColor colorWithRed:241/255.0 green:235/255.0 blue:222/255.0 alpha:1.0] set];
    CGContextFillRect(context, CGRectMake(0, 0, (COLUMN_COUNT + 1)* CHESS_WIDTH, (ROW_COUNT + 1) * CHESS_HEIGHT));
    
    int startX = CHESS_WIDTH;
    int startY = CHESS_HEIGHT;
    [[UIColor blackColor] set];
    for (int i = 0; i < ROW_COUNT; ++i) {
        CGContextFillRect(context, CGRectMake(startX, startY + i * CHESS_HEIGHT, (COLUMN_COUNT - 1) * CHESS_WIDTH, 1));
    }
    for (int i = 0; i < COLUMN_COUNT; ++i) {
        CGContextFillRect(context, CGRectMake(startX + i * CHESS_WIDTH, startY, 1, (ROW_COUNT - 1) * CHESS_HEIGHT));
    }
}

// 设置棋子，行数和列数都从1开始，[1,15][1,15]
- (void)setChess:(char)type withRow:(int)row withColumn:(int)column {
    chessMap[row-1][column-1] = type;
    chessRecord.push_back(std::pair<int, int>(row, column));
    
    int x = CHESS_WIDTH * column - CHESS_WIDTH / 2;
    int y = CHESS_HEIGHT * row - CHESS_HEIGHT / 2;
    ChessManView *chessView = [[ChessManView alloc] initWithType:type x:x y:y];
    [self addSubview:chessView];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint touchPoint = [[touches anyObject] locationInView:self];
    int row = (touchPoint.y + CHESS_HEIGHT / 2) / CHESS_HEIGHT;
    int column = (touchPoint.x + CHESS_WIDTH / 2) / CHESS_WIDTH;
    
    if (row >= 1 && row <= ROW_COUNT && column >= 1 && column <= COLUMN_COUNT) {
        char type = chessAI.getCurrentPlayer(chessMap);
        [self setChess:type withRow:row withColumn:column];
    }
}

- (void)restartChess {
    [self clearChessMap];
    for (UIView *view in self.subviews) {
        [view removeFromSuperview];
    }
}

- (void)regretChess {
    if (chessRecord.size()) {
        auto position = chessRecord.back();
        chessRecord.pop_back();
        int row = position.first;
        int column = position.second;
        chessMap[row-1][column-1] = SPACE;
        
        int x = CHESS_WIDTH * column - CHESS_WIDTH / 2;
        int y = CHESS_HEIGHT * row - CHESS_HEIGHT / 2;
        for (ChessManView *view in self.subviews) {
            if (view.x == x && view.y == y) {
                [view removeFromSuperview];
            }
        }
    }
}

- (void)AI {
    std::pair<int, int> position = chessAI.goAI(chessMap);
    char type = chessAI.getCurrentPlayer(chessMap);
    [self setChess:type withRow:position.first+1 withColumn:position.second+1];
}

- (void)clearChessMap {
    memset(chessMap, SPACE, sizeof(chessMap));
    chessRecord.clear();
}

@end




@implementation ChessManView

- (id)initWithType:(char)type x:(int)x y:(int)y {
    if (self = [super init]) {
        self.frame = CGRectMake(x, y, CHESS_WIDTH, CHESS_HEIGHT);
        self.backgroundColor = [UIColor clearColor];
        _type = type;
        _x = x;
        _y = y;
    }
    return self;
}

- (void)drawRect:(CGRect)rect {
    CGContextRef context = UIGraphicsGetCurrentContext();
    if (_type == BLACK_CHESS) {
        [[UIColor blackColor] set];
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
    } else if (_type == WHITE_CHESS) {
        [[UIColor grayColor] setStroke];
        [[UIColor whiteColor] setFill];
        CGContextStrokeEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
    }
}

@end

