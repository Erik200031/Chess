#ifndef CHECKER_FIGURE_H
#define CHECKER_FIGURE_H

#include "figure.h"

#define BLACK_FIGURE "X"
#define WHITE_FIGURE "O"

class Checker_figure : public Figure
{
public:
    inline Checker_figure();
    inline void set_collor(bool collor) override;
};

Checker_figure::Checker_figure()
{
    m_collor = true;
    m_figure = BLACK_FIGURE;
}

void Checker_figure::set_collor(bool collor)
{
    m_collor = collor;
    if(m_collor == BLACK) {
        m_figure = BLACK_FIGURE;
    }
    else {
        m_figure = WHITE_FIGURE;
    }
}

#endif //CHECKER_FIGURE_H