#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "../pieces/figure.h"
#include "../pieces/empty_figure.h"

#define DEFAULT_HEIGHT 8
#define DEFAULT_WIDTH 8

typedef std::vector<std::vector<std::unique_ptr<Figure>>> FIGURES;

class Board
{
public:
    Board();
    Board(int height, int width);
    Board(const Board& rhs) = default;
    Board(Board&& rhs) = default;
    Board& operator=(const Board& rhs) = default;
    Board& operator=(Board&& rhs) = default;
    virtual void print() const;
    const FIGURES& get_figures() const;
protected:
    FIGURES m_figures;
    int m_height;
    int m_width;
};

#endif //BOARD_H