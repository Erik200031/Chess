#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"

#define BLACK_BISHOP "♝"
#define WHITE_BISHOP "♗"

#define EMPTY " "

class Bishop : public Figure
{
public:
    inline Bishop();
    inline void set_collor(bool collor) override;
};

Bishop::Bishop()
{
    m_collor = true;
    m_figure = BLACK_BISHOP;
}

void Bishop::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_BISHOP;
    }
    else {
        m_figure = WHITE_BISHOP;
    }
}

#endif //BISHOP_H