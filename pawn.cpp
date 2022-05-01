#include "pawn.h" 

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