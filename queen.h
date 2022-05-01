#ifndef QUEEN_H
#define QUEEN_H

#include "rook.h"
#include "bishop.h"

#define BLACK_QUEEN "♛"
#define WHITE_QUEEN "♕"

class Queen : public Figure
{
public:
    Queen();
    void set_collor(bool collor) override;
};

#endif //QUEEN_H