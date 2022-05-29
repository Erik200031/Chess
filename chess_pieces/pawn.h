#ifndef PAWN_H
#define PAWN_H

#include "figure.h"

#define BLACK_PAWN "♟"
#define WHITE_PAWN "♙"

class Pawn : public Figure
{
public:
    inline Pawn();
    inline void set_collor(bool collor) override;
};

Pawn::Pawn()
{
    m_collor = true;
    m_figure = BLACK_PAWN;
}

void Pawn::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_PAWN;
    }
    else {
        m_figure = WHITE_PAWN;
    }
}

#endif //PAWN_H