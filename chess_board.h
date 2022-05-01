#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <math.h>

#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"


class Chess_board : public Board
{  
public:
    Chess_board();
    void print() const override;
};


#endif //CHESS_BOARD_H