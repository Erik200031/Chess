#ifndef KNIGHT_H
#define KNIGHT_H

#include "figure.h"

#define BLACK_KNIGHT "♞"
#define WHITE_KNIGHT "♘"

class Knight : public Figure
{
public:
    Knight();
    void set_collor(bool collor) override;
};


#endif //KNIGHT_H