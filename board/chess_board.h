#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <math.h>

#include "board.h"
#include "../chess_pieces/pawn.h"
#include "../chess_pieces/rook.h"
#include "../chess_pieces/knight.h"
#include "../chess_pieces/bishop.h"
#include "../chess_pieces/queen.h"
#include "../chess_pieces/king.h"


class Chess_board : public Board
{  
public:
    Chess_board();
    void print() const override;
};

#endif //CHESS_BOARD_H