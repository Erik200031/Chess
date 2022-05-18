#ifndef CHESS_H
#define CHESS_H

#include <unordered_map>
#include <utility>
#include <math.h>
#include <string>

#include "game.h"
#include "chess_board.h"

class Chess;
typedef std::unordered_map<std::string, void(Chess::*)(int, int)> STEP_FUNCTIONS;

class Chess : public Game, private Chess_board
{
public:
    Chess();
    void play() override;
private:
    bool check_black(int king_x, int king_y) const;
    bool check_white(int king_x, int king_y) const;
    void mate(bool collor);
    void no_one_win();
    bool verify_coordinates(int x, int y) const;
    std::pair<int, int> get_kings_position(bool color) const;
    bool check_all_available_steps();
    void view_current_available_steps(int at_x, int at_y);
    void view_current_pawn_available_steps(int at_x, int at_y);
    void view_current_rook_available_steps(int at_x, int at_y);
    void view_current_bishop_available_steps(int at_x, int at_y);
    void view_current_knight_available_steps(int at_x, int at_y);
    void view_current_king_available_steps(int at_x, int at_y);
    void view_current_queen_available_steps(int at_x, int at_y);
    bool is_king_attackable_by_pawn(int king_x, int king_y, bool color) const;
    bool is_king_attackable_by_knights(int king_x, int king_y, bool color) const;
    bool is_king_attackable_by_rook_or_queen(int king_x, int king_y, bool color) const;
    bool is_king_attackable_by_bishop_or_queen(int king_x, int king_y, bool color) const;
    bool is_meeting_kings(int king_x, int king_y, bool color) const;
    void change_pawn(int x, int y);
    void empty_steps(int at_x, int at_y);
    void input_coordinates();
    void reset();
    bool check_step(const std::string& input);
    std::pair<int, int> parse_input(const std::string& input);
private:
    int all_available_steps_count{};
    std::string current_available_steps{};
    std::string all_passed_steps{};
    STEP_FUNCTIONS step_functions;
    bool turn;
    bool castling{};
    bool end_game{};
    bool bad_input{};
    bool pawn_different_steps{};
    ~Chess() = default;
};

#endif //CHESS_H