#ifndef CHECKERS_H
#define CHECKERS_H

#include "game.h"
#include "../board/checkers_board.h"

class Checkers : public Game, private Checkers_board
{
public:
    void play() override;
    ~Checkers() = default;
protected:
    void input_coordinates();
    bool verify_coordinates(int x, int y) const;
    std::pair<int, int> parse_input(const std::string& input);
    void view_current_available_steps(int at_x, int at_y);
    void view_current_available_steps_left_non_queen(int at_x, int at_y);
    void view_current_available_steps_right_non_queen(int at_x, int at_y);
private:
    void view_current_available_steps_left_non_queen_helper(int at_x, int at_y);
    bool m_turn{};
    std::string current_available_steps{};
    bool m_back_eat_flag{};
};

#endif //CHECKERS_H