#include "bishop.h"

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