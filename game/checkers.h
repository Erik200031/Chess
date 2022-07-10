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
    bool check_step(const std::string& input);
    bool is_have_any_steps(int at_x);
    std::pair<int, int> parse_input(const std::string& input);
    void view_current_available_steps(int at_x, int at_y);
    void view_current_available_steps_left_non_queen(int at_x, int at_y);
    void view_current_available_steps_right_non_queen(int at_x, int at_y);
    void erase_enemys_piece(int at_x, int at_y, int to_x, int to_y);
private:
    bool m_turn{};
    std::string current_available_steps{};
    bool m_back_eat_flag{};
    bool bad_input{};
};

#endif //CHECKERS_H