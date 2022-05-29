#ifndef EMPTY_FIGURE_H
#define EMPTY_FIGURE_H

#include "figure.h"

#define EMPTY " "

class Empty_figure : public Figure 
{
public:
    inline Empty_figure();
    inline void set_collor(bool collor) override {}
};

Empty_figure::Empty_figure()
{
    m_collor = true;
    m_figure = EMPTY;
}

#endif //EMPTYFIGURE_H