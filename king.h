#ifndef KING_H
#define KING_H

#include "figure.h"

#define BLACK_KING "♚"
#define WHITE_KING "♔"

class King : virtual public Figure
{
public:
    inline King();
    inline void set_collor(bool collor) override;
};

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

#endif //KING_H