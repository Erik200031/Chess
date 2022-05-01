#ifndef AVAILABLE_FIGURE_H
#define AVAILABLE_FIGURE_H

#include "figure.h"

#define AVAILABLE "⏎"

class Available : public Figure 
{
public:
    Available();
    void set_collor(bool collor) override {}
};

#endif //AVAILABLE_FIGURE_H