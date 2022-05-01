#include "rook.h"

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