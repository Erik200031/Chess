#ifndef EMPTY_FIGURE_H
#define EMPTY_FIGURE_H

#include "figure.h"

#define EMPTY " "

class Empty_figure : public Figure 
{
public:
    Empty_figure();
    void set_collor(bool collor) override {}
};

#endif //EMPTYFIGURE_H