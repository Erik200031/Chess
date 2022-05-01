#ifndef ROOK_H
#define ROOK_H

#include "figure.h"

#define BLACK_ROOK "♜"
#define WHITE_ROOK "♖"

class Rook : public Figure
{
public:
    Rook();
    void set_collor(bool collor) override;
};

#endif //ROOK_H