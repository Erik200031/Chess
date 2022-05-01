#include "queen.h"

Queen::Queen()
{
    m_collor = true;
    m_figure = BLACK_QUEEN;
}

void Queen::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_QUEEN;
    }
    else {
        m_figure = WHITE_QUEEN;
    }
}