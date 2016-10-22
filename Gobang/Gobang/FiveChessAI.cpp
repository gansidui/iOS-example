//
//  FiveChessAI.cpp
//  Gobang
//
//  Created by lijie on 2016/10/22.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#include "FiveChessAI.hpp"

FiveChessAI::FiveChessAI() {
    
}

FiveChessAI::~FiveChessAI() {
    
}

std::pair<int, int> FiveChessAI::goAI(char chessMap[15][15]) {
    FiveChess fiveChess;
    
    // 设置禁手
    fiveChess.SetKinjite(true);
    
    // 检测计算机执棋颜色
    int nBlack = 0, nWhite = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (chessMap[i][j] == BLACK_CHESS) ++nBlack;
            if (chessMap[i][j] == WHITE_CHESS) ++nWhite;
        }
    }
    if (nWhite < nBlack) {
        fiveChess.cComputer = WHITE_CHESS;
        fiveChess.cPeople = BLACK_CHESS;
        
    } else {
        fiveChess.cComputer = BLACK_CHESS;
        fiveChess.cPeople = WHITE_CHESS;
    }
    
    // 如果是空白棋盘，则下中元
    if (nBlack == 0 && nWhite == 0) {
        return std::pair<int, int>(7, 7);
    }

    // 拷贝棋盘
    fiveChess.InitChessMap();
    memcpy(&(fiveChess.chessMap[0][0]), &(chessMap[0][0]), 15*15);
    
    // VC 的攻击深度和防御深度设置在这里初始化，可以动态设置
    fiveChess.VCDEPTH = 3;
    fiveChess.VCDEPTH_END = 3;
    fiveChess.VCDEPTH_DIS =1;
    
    fiveChess.VCDE_DEPTH = 3;
    fiveChess.VCDE_DEPTH_END = 3;
    fiveChess.VCDE_DEPTH_DIS = 1;
    
    fiveChess.grade = 2;
    
    fiveChess.AI();
    
    return std::pair<int, int>(fiveChess.comX, fiveChess.comY);
}

char FiveChessAI::getCurrentPlayer(char chessMap[15][15]) {
    int nBlack = 0, nWhite = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (chessMap[i][j] == BLACK_CHESS) ++nBlack;
            if (chessMap[i][j] == WHITE_CHESS) ++nWhite;
        }
    }
    if (nWhite < nBlack) {
        return WHITE_CHESS;
    }
    return BLACK_CHESS;
}

