//
//  ChessBoardView.m
//  Gobang
//
//  Created by lijie on 2016/10/21.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#import "ChessBoardView.h"

#define ROW_COUNT    (15)
#define COLUMN_COUNT (15)
#define CHESS_WIDTH  (20)
#define CHESS_HEIGHT (20)


@implementation ChessBoardView

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
    
    [self setChess:CHESS_TYPE_WHITE withRow:1 withColumn:1];
    [self setChess:CHESS_TYPE_BLACK withRow:1 withColumn:2];
    [self setChess:CHESS_TYPE_BLACK withRow:2 withColumn:1];
    [self setChess:CHESS_TYPE_BLACK withRow:5 withColumn:5];
    [self setChess:CHESS_TYPE_BLACK withRow:5 withColumn:6];
    [self setChess:CHESS_TYPE_BLACK withRow:8 withColumn:8];
}

- (void)setChess:(int)type withRow:(int)row withColumn:(int)column {
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
        int type = CHESS_TYPE_BLACK;
        [self setChess:type withRow:row withColumn:column];
    }
}

@end




@implementation ChessManView

- (id)initWithType:(int)type x:(int)x y:(int)y {
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
    if (_type == CHESS_TYPE_BLACK) {
        [[UIColor blackColor] set];
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
    } else if (_type == CHESS_TYPE_WHITE) {
        [[UIColor grayColor] setStroke];
        [[UIColor whiteColor] setFill];
        CGContextStrokeEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
        CGContextFillEllipseInRect(context, CGRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
    }
}

@end

