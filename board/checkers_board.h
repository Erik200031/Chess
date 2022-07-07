#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include "board.h"
#include "../pieces/checker_figure.h"
#include "../pieces/queen.h"


class Checkers_board : public Board
{
public:
    Checkers_board();
    void print() const override;
};

#endif //CHECKERS_BOARD_H