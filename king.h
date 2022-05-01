#ifndef KING_H
#define KING_H

#include "figure.h"

#define BLACK_KING "♚"
#define WHITE_KING "♔"

class King : virtual public Figure
{
public:
    King();
    void set_collor(bool collor) override;
};

#endif //KING_H