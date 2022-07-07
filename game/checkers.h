#ifndef CHECKERS_H
#define CHECKERS_H

#include "game.h"
#include "../board/checkers_board.h"

class Checkers : public Game, private Checkers_board
{
public:
    void play() override;
protected:
    void input_coordinates();
    bool verify_coordinates(int x, int y) const;
    std::pair<int, int> parse_input(const std::string& input);
private:
    bool turn;
};





#endif //CHECKERS_H