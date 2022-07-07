#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <math.h>

#include "board.h"
#include "../pieces/pawn.h"
#include "../pieces/rook.h"
#include "../pieces/knight.h"
#include "../pieces/bishop.h"
#include "../pieces/queen.h"
#include "../pieces/king.h"


class Chess_board : public Board
{  
public:
    Chess_board();
    void print() const override;
};

#endif //CHESS_BOARD_H