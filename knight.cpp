#include "knight.h"

Knight::Knight()
{
    m_collor = true;
    m_figure = BLACK_KNIGHT;
}

void Knight::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_KNIGHT;
    }
    else {
        m_figure = WHITE_KNIGHT;
    }
}