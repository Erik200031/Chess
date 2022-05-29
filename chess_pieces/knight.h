#ifndef KNIGHT_H
#define KNIGHT_H

#include "figure.h"

#define BLACK_KNIGHT "♞"
#define WHITE_KNIGHT "♘"

class Knight : public Figure
{
public:
    inline Knight();
    inline void set_collor(bool collor) override;
};

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

#endif //KNIGHT_H