//
//  FiveChessAI.hpp
//  Gobang
//
//  Created by lijie on 2016/10/22.
//  Copyright © 2016年 gansidui. All rights reserved.
//

#ifndef FiveChessAI_hpp
#define FiveChessAI_hpp

#include "FiveChess.hpp"

/**
 * 基于禁手规则
 */

class FiveChessAI {
public:
    FiveChessAI();
    virtual ~FiveChessAI();
    
    // 传入棋盘，返回落子点(下标从0开始)
    // 内部会检测计算机执黑还是执白
    std::pair<int, int> goAI(char chessMap[15][15]);
    
    
    // 得到当前该谁下，用于界面调试
    char getCurrentPlayer(char chessMap[15][15]);
    
};

#endif /* FiveChessAI_hpp */
