#ifndef ROOK_H
#define ROOK_H

#include "figure.h"

#define BLACK_ROOK "♜"
#define WHITE_ROOK "♖"

class Rook : public Figure
{
public:
    inline Rook();
    inline void set_collor(bool collor) override;
};

Rook::Rook()
{
    m_collor = true;
    m_figure = BLACK_ROOK;
}

void Rook::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_ROOK;
    }
    else {
        m_figure = WHITE_ROOK;
    }
}

#endif //ROOK_H