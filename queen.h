#ifndef QUEEN_H
#define QUEEN_H

#include "rook.h"
#include "bishop.h"

#define BLACK_QUEEN "♛"
#define WHITE_QUEEN "♕"

class Queen : public Figure
{
public:
    inline Queen();
    inline void set_collor(bool collor) override;
};

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

#endif //QUEEN_H