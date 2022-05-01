#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"

#define BLACK_BISHOP "♝"
#define WHITE_BISHOP "♗"

#define EMPTY " "

class Bishop : public Figure
{
public:
    Bishop();
    void set_collor(bool collor) override;
};

#endif //BISHOP_H