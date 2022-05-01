#ifndef PAWN_H
#define PAWN_H

#include "figure.h"

#define BLACK_PAWN "♟"
#define WHITE_PAWN "♙"

class Pawn : public Figure
{
public:
    Pawn();
    void set_collor(bool collor) override;
};

#endif //PAWN_H