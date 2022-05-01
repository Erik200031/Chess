#include "king.h"

King::King()
{
    m_collor = true;
    m_figure = BLACK_KING;
}

void King::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_KING;
    }
    else {
        m_figure = WHITE_KING;
    }
}