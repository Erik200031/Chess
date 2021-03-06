#include "chess.h"

Chess::Chess()
{
    step_functions.emplace(WHITE_PAWN, &Chess::view_current_pawn_available_steps);
    step_functions.emplace(BLACK_PAWN, &Chess::view_current_pawn_available_steps);
    step_functions.emplace(WHITE_BISHOP, &Chess::view_current_bishop_available_steps);
    step_functions.emplace(BLACK_BISHOP, &Chess::view_current_bishop_available_steps);    
    step_functions.emplace(WHITE_ROOK, &Chess::view_current_rook_available_steps);
    step_functions.emplace(BLACK_ROOK, &Chess::view_current_rook_available_steps);
    step_functions.emplace(WHITE_KING, &Chess::view_current_king_available_steps);
    step_functions.emplace(BLACK_KING, &Chess::view_current_king_available_steps);
    step_functions.emplace(WHITE_KNIGHT, &Chess::view_current_knight_available_steps);
    step_functions.emplace(BLACK_KNIGHT, &Chess::view_current_knight_available_steps);
    step_functions.emplace(WHITE_QUEEN, &Chess::view_current_queen_available_steps);
    step_functions.emplace(BLACK_QUEEN, &Chess::view_current_queen_available_steps); 
    step_functions.emplace(EMPTY, &Chess::empty_steps);
}

bool Chess::check_black(int king_x, int king_y) const
{
    return is_king_attackable_by_pawn(king_x, king_y, BLACK) ||
    is_king_attackable_by_knights(king_x, king_y, BLACK) ||
    is_king_attackable_by_rook_or_queen(king_x, king_y, BLACK) || 
    is_king_attackable_by_bishop_or_queen(king_x, king_y, BLACK) ||
    is_meeting_kings(king_x, king_y, BLACK);
}

bool Chess::check_white(int king_x, int king_y) const
{
    return is_king_attackable_by_pawn(king_x, king_y, WHITE) ||
    is_king_attackable_by_knights(king_x, king_y, WHITE) ||
    is_king_attackable_by_rook_or_queen(king_x, king_y, WHITE) || 
    is_king_attackable_by_bishop_or_queen(king_x, king_y, WHITE) ||
    is_meeting_kings(king_x, king_y, WHITE);
}

void Chess::mate(bool collor)
{
    end_game = true;
    collor == BLACK ? std::cout << "\nBlack Wins!\n" : std::cout << "\nWhite Wins!\n";
    std::cout << "PLAY AGAIN ?\n";
    std::cout << "YES  or NO\n";
    std::string answer{};
    std::cin >> answer;
    if(answer == "YES" || answer == "yes") {
        reset();
        play();
    }
    else {
        exit(0);
    }
}

bool Chess::verify_coordinates(int x, int y) const 
{
    return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

bool Chess::check_step(const std::string& input)
{
    std::string tmp{};
    for(int i = 0; i < current_available_steps.size(); ++i) {
        if(current_available_steps[i] != ' ') {
            tmp += current_available_steps[i];
        } else {
            if(input == tmp) {
                return true;
            }
            tmp = "";
        }
    }
    if(input == tmp) {
        return true;
    }
    return false;
}

void Chess::input_coordinates() 
{
    pawn_different_steps = false;
    castling = false;
    std::pair<int, int> white_king_pos = get_kings_position(WHITE);
    std::pair<int, int> black_king_pos = get_kings_position(BLACK);
    if(is_all_available_figures_are_kings()) {
        no_one_win();
    }
    if(turn == WHITE && 
    check_white(white_king_pos.first, white_king_pos.second) && check_all_available_steps()) {
        mate(BLACK);
    }
    if(turn == BLACK && 
    check_black(black_king_pos.first, black_king_pos.second) && check_all_available_steps()) {
        mate(WHITE);
    }
    if(!check_black(black_king_pos.first, black_king_pos.second) &&
     !check_white(white_king_pos.first, white_king_pos.second) && 
     check_all_available_steps()) {
        no_one_win();
    }
    turn == WHITE ? std::cout << "\nTURN -> WHITE\n" : std::cout <<  "\nTURN -> BLACK\n";
    if(bad_input) {
        std::cout << "Bad input!\n Try again";
    }
    std::cout << "\nAt: ";
    std::string at_input{};
    std::cin >> at_input;
    at_input[0] = toupper(at_input[0]);
    current_available_steps = at_input;
    std::pair<int, int> tmp = parse_input(at_input);
    while(tmp.first == -1) {
        print();
        std::cout << "\nBad input! Try again\n";
        std::cout << "\nAt: ";
        std::cin >> at_input;
        at_input[0] = toupper(at_input[0]);
        current_available_steps = at_input;
        tmp = parse_input(at_input);
    }
    int at_y = tmp.first;
    int at_x = m_figures.size() - 1 - tmp.second + 1;
     if((m_figures[at_x][at_y]->get_figure() != EMPTY && 
    m_figures[at_x][at_y]->get_collor() == BLACK && 
    turn == BLACK) ||
    (m_figures[at_x][at_y]->get_figure() != EMPTY && 
    m_figures[at_x][at_y]->get_collor() == WHITE && 
    turn == WHITE)) {
        view_current_available_steps(at_x, at_y);
        if(current_available_steps.size() <= 2) {
            while(tmp.first == -1 || current_available_steps.size() <= 2) {
                print();
                std::cout << "No available steps! ";
                std::cout << "\nAt: ";
                std::cin >> at_input;
                at_input[0] = toupper(at_input[0]);
                current_available_steps = at_input;
                tmp = parse_input(at_input);
                at_y = tmp.first;
                at_x = m_figures.size() - 1 - tmp.second + 1;
                view_current_available_steps(at_x, at_y);
            }
        }
    }
    if((m_figures[at_x][at_y]->get_figure() != EMPTY && 
    m_figures[at_x][at_y]->get_collor() == BLACK && 
    turn == BLACK) ||
    (m_figures[at_x][at_y]->get_figure() != EMPTY && 
    m_figures[at_x][at_y]->get_collor() == WHITE && 
    turn == WHITE)) {
        std::cout << "Available steps -> " << current_available_steps;
        std::cout << "\nTo: ";
        std::string to_input{};
        std::cin >> to_input;
        to_input[0] = toupper(to_input[0]);
        tmp = parse_input(to_input);
        while(tmp.first == -1) {    
            print();
            std::cout << "\nBad input! Try again\n";
            if(current_available_steps.size() <= 2) {
                std::cout << "No available steps! ";
            } else {
                std::cout << "Available steps -> " << current_available_steps;
            }
            std::cout << "\nTo: ";
            std::cin >> to_input;
            to_input[0] = toupper(to_input[0]);
            tmp = parse_input(to_input);
        }
        int to_y = tmp.first;
        int to_x = m_figures.size() - tmp.second;
        if(check_step(to_input)) {
            m_figures[to_x][to_y].reset(m_figures[at_x][at_y].release());
            m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
            if(pawn_different_steps && to_y - at_y == -1) {
                m_figures[at_x][at_y - 1].reset(std::make_unique<Empty_figure>().release());
            }
            else if(pawn_different_steps && to_y - at_y == 1) {
                m_figures[at_x][at_y + 1].reset(std::make_unique<Empty_figure>().release());
            }
            if(m_figures[to_x][to_y]->get_figure() == BLACK_PAWN && to_x == 7 || 
            m_figures[to_x][to_y]->get_figure() == WHITE_PAWN && to_x == 0) {
                change_pawn(to_x, to_y);
            }
            if(castling && turn == WHITE && to_x == 7 && to_y == 6) {
                m_figures[to_x][to_y - 1].reset(m_figures[to_x][to_y + 1].release());
                m_figures[to_x][to_y + 1].reset(std::make_unique<Empty_figure>().release());
            }
            if(castling && turn == WHITE && to_x == 7 && to_y == 2) {
                m_figures[to_x][to_y + 1].reset(m_figures[to_x][to_y - 2].release());
                m_figures[to_x][to_y - 2].reset(std::make_unique<Empty_figure>().release());
            }
            if(castling && turn == BLACK && to_x == 0 && to_y == 6) {
                m_figures[to_x][to_y - 1].reset(m_figures[to_x][to_y + 1].release());
                m_figures[to_x][to_y + 1].reset(std::make_unique<Empty_figure>().release());
            }
            if(castling && turn == BLACK && to_x == 0 && to_y == 2) {
                m_figures[to_x][to_y + 1].reset(m_figures[to_x][to_y - 2].release());
                m_figures[to_x][to_y - 2].reset(std::make_unique<Empty_figure>().release());
            }
            turn == BLACK ? turn = WHITE: turn = BLACK;
            all_passed_steps += at_input + to_input + ' ';
            bad_input = false;
        } else {
            bad_input = true;
        }
    }
}

std::pair<int, int> Chess::parse_input(const std::string& input)
{
    if(input.size() <= 1 || input.size() > 2) {
        return std::make_pair(-1, -1);
    }
    else if(((input[0] - 65 >= 0) && (input[0] - 65 <= 7)) &&
     (input[1] >= '1') && (input[1] <= '8')) {
        return std::make_pair(input[0] - 65, std::stoi(input.substr(1,2)));
    }
    return std::make_pair(-1, -1);
}

bool Chess::check_all_available_steps()
{
    all_available_steps_count = 0;
    if(turn == BLACK) {
        for(int i = 0; i < m_figures.size(); ++i) {
            for(int j = 0; j < m_figures[i].size(); ++j) {
                if(m_figures[i][j]->get_figure() != EMPTY && 
                m_figures[i][j]->get_collor() == BLACK) {
                    view_current_available_steps(i, j);
                }
            }
        }
    }
    else if(turn == WHITE) {
        for(int i = 0; i < m_figures.size(); ++i) {
            for(int j = 0; j < m_figures[i].size(); ++j) {
                if(m_figures[i][j]->get_figure() != EMPTY && 
                m_figures[i][j]->get_collor() == WHITE) {
                    view_current_available_steps(i, j);
                }
            }
        }
    }
    return !all_available_steps_count;
}

void Chess::view_current_available_steps(int at_x, int at_y)
{
    (this->*step_functions[m_figures[at_x][at_y]->get_figure()])(at_x, at_y);
}

void Chess::view_current_pawn_available_steps(int at_x, int at_y)
{
    bool color;
    bool (Chess::*ptr)(int, int) const;
    int initial_x {};
    int en_passant_x {};
    int step_direction {};
    int enemy_last_pawn_step_one {};
    int enemy_last_pawn_step_two {};
    std::string pawn_for_en_passant {};
    if(m_figures[at_x][at_y]->get_figure() == BLACK_PAWN) {
        initial_x = 1;
        en_passant_x = 4;
        step_direction = 1;
        enemy_last_pawn_step_one = 2;
        enemy_last_pawn_step_two = 4;
        pawn_for_en_passant = WHITE_PAWN;
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        initial_x = 6;
        en_passant_x = 3;
        step_direction = -1;
        enemy_last_pawn_step_one = 7;
        enemy_last_pawn_step_two = 5;
        pawn_for_en_passant = BLACK_PAWN;
        ptr = &Chess::check_white;
        color = WHITE;
    }
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    if(at_x == initial_x) {
        view_current_pawn_initial_steps(at_x, at_y, ptr, step_direction, color, tmp_steps);
    }
    else if((at_x > initial_x && color == BLACK) ||
    (at_x < initial_x && color == WHITE)) {
        view_current_pawn_not_initial_steps(at_x, at_y, ptr, step_direction, color, tmp_steps);
        view_current_pawn_en_passant_steps(at_x, at_y, ptr, step_direction, color, tmp_steps,
         en_passant_x, enemy_last_pawn_step_one, enemy_last_pawn_step_two, pawn_for_en_passant);
    }
}

void Chess::view_current_pawn_initial_steps
    (int at_x, int at_y, bool (Chess::*ptr)(int, int) const,
    int step_direction, bool color, const std::string& tmp_steps)
{
    if(m_figures[at_x + step_direction][at_y]->get_figure() == EMPTY) {
        m_figures[at_x + step_direction][at_y].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps =  " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y].release());
        m_figures[at_x + step_direction][at_y] = std::make_unique<Empty_figure>();   
    }
    if(m_figures[at_x + 2 * step_direction][at_y]->get_figure() == EMPTY && 
    m_figures[at_x + step_direction][at_y]->get_figure() == EMPTY) {
        m_figures[at_x + 2 * step_direction][at_y].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[1] -= 2 * step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps =  " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + 2 * step_direction][at_y].release());
        m_figures[at_x + 2 * step_direction][at_y] = std::make_unique<Empty_figure>();
    }
    if (verify_coordinates(at_x + step_direction, at_y + 1) && 
    (m_figures[at_x + step_direction][at_y + 1]->get_figure() != EMPTY &&
    m_figures[at_x + step_direction][at_y + 1]->get_collor() != color)) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] += 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(tmp.release());
    } 
    if(verify_coordinates(at_x + step_direction, at_y - 1) && 
    (m_figures[at_x + step_direction][at_y - 1]->get_figure() != EMPTY &&
    m_figures[at_x + step_direction][at_y - 1]->get_collor() != color)) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + 1][at_y - 1].release());
        m_figures[at_x + 1][at_y - 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] -= 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y - 1].release());
        m_figures[at_x + step_direction][at_y - 1].reset(tmp.release());
    }
}

void Chess::view_current_pawn_not_initial_steps
    (int at_x, int at_y, bool (Chess::*ptr)(int, int) const,
    int step_direction, bool color, const std::string& tmp_steps)
{
    if(verify_coordinates(at_x + step_direction, at_y) && 
    (m_figures[at_x + step_direction][at_y]->get_figure() == EMPTY)) {
        m_figures[at_x + step_direction][at_y].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        } 
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y].release());
        m_figures[at_x + step_direction][at_y] = std::make_unique<Empty_figure>();
    }
    if(verify_coordinates(at_x + step_direction, at_y - 1) && 
    (m_figures[at_x + step_direction][at_y - 1]->get_figure() != EMPTY) &&
    (m_figures[at_x + step_direction][at_y - 1]->get_collor() != color)) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + step_direction][at_y - 1].release());
        m_figures[at_x + step_direction][at_y - 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
                    std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] -= 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y - 1].release());
        m_figures[at_x + step_direction][at_y - 1].reset(tmp.release());
    }
    if(verify_coordinates(at_x + step_direction, at_y + 1) && 
    (m_figures[at_x + step_direction][at_y + 1]->get_figure() != EMPTY) &&
    (m_figures[at_x + step_direction][at_y + 1]->get_collor() != color)) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] += 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(tmp.release());
    }
}

void Chess::view_current_pawn_en_passant_steps
    (int at_x, int at_y, bool (Chess::*ptr)(int, int) const,
    int step_direction, bool color, const std::string& tmp_steps,
    int en_passant_x, int enemy_last_pawn_step_one, 
    int enemy_last_pawn_step_two, const std::string& pawn_for_en_passant)
{
    if(at_x == en_passant_x && verify_coordinates(at_x, at_y - 1) &&
    (m_figures[at_x][at_y - 1]->get_figure() == pawn_for_en_passant) && 
    (at_y - 1 == all_passed_steps[all_passed_steps.size() - 5] - 'A') &&
    (at_y - 1 == all_passed_steps[all_passed_steps.size() - 3] - 'A') &&
    (all_passed_steps[all_passed_steps.size() - 4] - '0' == enemy_last_pawn_step_one) &&
    (all_passed_steps[all_passed_steps.size() - 2] - '0' == enemy_last_pawn_step_two)
    ) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + step_direction][at_y - 1].release());
        m_figures[at_x + step_direction][at_y - 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] -= 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y - 1].release());
        m_figures[at_x + step_direction][at_y - 1].reset(tmp.release());
        pawn_different_steps = true;
    }
    if(at_x ==  en_passant_x && verify_coordinates(at_x, at_y + 1) &&
    m_figures[at_x][at_y + 1]->get_figure() == pawn_for_en_passant && 
    (at_y + 1 == all_passed_steps[all_passed_steps.size() - 5] - 'A') &&
    (at_y + 1 == all_passed_steps[all_passed_steps.size() - 3] - 'A') &&
    (all_passed_steps[all_passed_steps.size() - 4] - '0' == enemy_last_pawn_step_one) &&
    (all_passed_steps[all_passed_steps.size() - 2] - '0' == enemy_last_pawn_step_two)
    ) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] += 1;
            tmp[1] -= step_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[at_x + step_direction][at_y + 1].release());
        m_figures[at_x + step_direction][at_y + 1].reset(tmp.release());
        pawn_different_steps = true;
    }
}

void Chess::view_current_knight_available_steps(int at_x, int at_y)
{
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    bool color;
    bool (Chess::*ptr)(int, int) const;
    if(m_figures[at_x][at_y]->get_figure() == BLACK_KNIGHT) {
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        ptr = &Chess::check_white;
        color = WHITE;
    }
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 2, at_y + 1, 2, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 2, at_y + 1, -2, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 2, at_y - 1, -2, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 2, at_y - 1, 2, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 1, at_y + 2, 1, 2, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 1, at_y - 2, 1, -2, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 1, at_y + 2, -1, 2, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 1, at_y - 2, -1, -2, color, ptr, tmp_steps);
}

void Chess::view_current_rook_available_steps(int at_x, int at_y)
{
    bool color;
    bool (Chess::*ptr)(int, int) const;
    if(m_figures[at_x][at_y]->get_figure() == BLACK_ROOK) {
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        ptr = &Chess::check_white;
        color = WHITE;
    }
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x + 1, at_y, 1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x - 1, at_y, -1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x, at_y + 1, 0, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x, at_y - 1, 0, -1, color, ptr, tmp_steps);
}

void Chess::view_current_bishop_available_steps(int at_x, int at_y)
{
    bool color;
    bool (Chess::*ptr)(int, int) const;
    if(m_figures[at_x][at_y]->get_figure() == BLACK_BISHOP) {
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        ptr = &Chess::check_white;
        color = WHITE;
    }
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x + 1, at_y + 1, 1, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x + 1, at_y - 1, 1, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x - 1, at_y + 1, -1, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x - 1, at_y - 1, -1, -1, color, ptr, tmp_steps);
}

void Chess::view_current_king_available_steps(int at_x, int at_y)
{
    bool color;
    bool (Chess::*ptr)(int, int) const;
    if(m_figures[at_x][at_y]->get_figure() == BLACK_KING) {
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        ptr = &Chess::check_white;
        color = WHITE;
    }
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    std::string tmp = tmp_steps;
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 1, at_y - 1, -1, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 1, at_y, -1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x - 1, at_y + 1, -1, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x, at_y - 1, 0, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x, at_y + 1, 0, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 1, at_y - 1, 1, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 1, at_y, 1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_king_pawn_knight
    (at_x, at_y, at_x + 1, at_y + 1, 1, 1, color, ptr, tmp_steps);
    int at_x_for_castle {};
    int at_y_for_castle {};
    std::string rook {};
    if(color == BLACK) {
        at_x_for_castle = 0;
        at_y_for_castle = 4;
        rook = BLACK_ROOK;
    } else {
        at_x_for_castle = 7;
        at_y_for_castle = 4;
        rook = WHITE_ROOK;
    }
    evaluate_castle_post_move
    (at_x, at_y, at_x_for_castle, at_y_for_castle, color, ptr, rook, tmp_steps);
}

void Chess::evaluate_castle_post_move
    (int at_x, int at_y, int at_x_for_castle, int at_y_for_castle,
    bool color, bool (Chess::*ptr)(int, int) const,
    const std::string& rook, const std::string& tmp_steps)
{
    evaluate_king_side_castle_post_move
    (at_x, at_y, at_x_for_castle, at_y_for_castle, color, ptr, rook, tmp_steps);
    evaluate_queen_side_castle_post_move
    (at_x, at_y, at_x_for_castle, at_y_for_castle, color, ptr, rook, tmp_steps);
}

void Chess::evaluate_king_side_castle_post_move
    (int at_x, int at_y, int at_x_for_castle, int at_y_for_castle,
    bool color, bool (Chess::*ptr)(int, int) const,
    const std::string& rook, const std::string& tmp_steps) 
{
    if(at_x == at_x_for_castle && at_y == at_y_for_castle &&
    m_figures[at_x][at_y + 1]->get_figure() == EMPTY && 
    m_figures[at_x][at_y + 2]->get_figure() == EMPTY &&
    m_figures[at_x][at_y + 3]->get_figure() == rook) {
        std::string tmp = tmp_steps;
        std::string tmpp = "";
        for(int i = 0; i < all_passed_steps.size(); ++i) {
            if(all_passed_steps.size() >= 4) {
                if(all_passed_steps[i] != ' ') {
                    tmpp += all_passed_steps[i];
                }
                else if(all_passed_steps[i] == ' ') {
                    if(tmpp[0] - 'A' == 4 && tmpp[1] - '0' == at_x_for_castle) {
                        break;
                    }
                    if(tmpp[0] - 'A' == 7 && tmpp[1] - '0' == at_x_for_castle) {
                        break;
                    }
                    tmpp = "";
                }
            }
        }
        if(!(tmpp[0] - 'A' == 4 && tmpp[1] - '0' == at_x_for_castle)) {
            tmpp = "";
        }
        if(!(tmpp[0] - 'A' == 7 && tmpp[1] - '0' == at_x_for_castle)) {
            tmpp = "";
        }
        std::cout << tmpp << "\n";
        if(tmpp == "") {
            m_figures[at_x][at_y + 1].reset(m_figures[at_x][at_y].release());
            m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
            std::pair<int, int> king_pos = get_kings_position(color);
            if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                m_figures[at_x][at_y + 2].reset(m_figures[at_x][at_y + 1].release());
                m_figures[at_x][at_y + 1] = std::make_unique<Empty_figure>();
            std::pair<int, int> king_pos = get_kings_position(color);
            if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                    tmp[0] += 2;
                    current_available_steps = tmp + current_available_steps;
                    current_available_steps = " " + current_available_steps;
                    ++all_available_steps_count;
                    castling = true;
                } 
                m_figures[at_x][at_y].reset(m_figures[at_x][at_y + 2].release());
                m_figures[at_x][at_y + 2].reset(std::make_unique<Empty_figure>().release());
            } else {
                m_figures[at_x][at_y].reset(m_figures[at_x][at_y + 1].release());
                m_figures[at_x][at_y + 1].reset(std::make_unique<Empty_figure>().release());
            }
        }
    }
}

void Chess::evaluate_queen_side_castle_post_move
    (int at_x, int at_y, int at_x_for_castle, int at_y_for_castle,
    bool color, bool (Chess::*ptr)(int, int) const,
    const std::string& rook, const std::string& tmp_steps) 
{
    if(at_x == at_x_for_castle && at_y == at_y_for_castle &&
    m_figures[at_x][at_y - 1]->get_figure() == EMPTY && 
    m_figures[at_x][at_y - 2]->get_figure() == EMPTY &&
    m_figures[at_x][at_y - 3]->get_figure() == EMPTY &&
    m_figures[at_x][at_y - 4]->get_figure() == rook) {
        std::string tmp = tmp_steps;
        std::string tmpp = "";
        for(int i = 0; i < all_passed_steps.size(); ++i) {
            if(all_passed_steps.size() >= 4) {
                if(all_passed_steps[i] != ' ') {
                    tmpp += all_passed_steps[i];
                }
                else if(all_passed_steps[i] == ' ') {
                    if(tmpp[0] - 'A' == at_y_for_castle && tmpp[1] - '0' == at_x_for_castle) {
                        break;
                    }
                    if(tmpp[0] - 'A' == at_x_for_castle && tmpp[1] - '0' == 0) {
                        break;
                    }
                    tmpp = "";
                }
            }
        }
        if(!(tmpp[0] - 'A' == at_y_for_castle && tmpp[1] - '0' == at_x_for_castle)) {
            tmpp = "";
        }
        if(!(tmpp[0] - 'A' == at_x_for_castle && tmpp[1] - '0' == 0)) {
            tmpp = "";
        }
        if(tmpp == "") {
            m_figures[at_x][at_y - 1].reset(m_figures[at_x][at_y].release());
            m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
            std::pair<int, int> king_pos = get_kings_position(color);
            if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                m_figures[at_x][at_y - 2].reset(m_figures[at_x][at_y - 1].release());
                m_figures[at_x][at_y - 1] = std::make_unique<Empty_figure>();
            std::pair<int, int> king_pos = get_kings_position(color);
            if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                    tmp[0] -= 2;
                    current_available_steps = tmp + current_available_steps;
                    current_available_steps = " " + current_available_steps;
                    ++all_available_steps_count;
                    castling = true;
                } 
                m_figures[at_x][at_y].reset(m_figures[at_x][at_y - 2].release());
                m_figures[at_x][at_y - 2].reset(std::make_unique<Empty_figure>().release());
            } else {
                m_figures[at_x][at_y].reset(m_figures[at_x][at_y - 1].release());
                m_figures[at_x][at_y - 1].reset(std::make_unique<Empty_figure>().release());
            }  
        }
    }
}

void Chess::view_current_queen_available_steps(int at_x, int at_y)
{
    bool color;
    bool (Chess::*ptr)(int, int) const;
    if(m_figures[at_x][at_y]->get_figure() == BLACK_QUEEN) {
        ptr = &Chess::check_black;
        color = BLACK;
    } else {
        ptr = &Chess::check_white;
        color = WHITE;
    }
    std::string tmp_steps = current_available_steps;
    current_available_steps = "";
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x + 1, at_y, 1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x - 1, at_y, -1, 0, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x, at_y + 1, 0, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_rook_queen
    (at_x, at_y, at_x, at_y - 1, 0, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x + 1, at_y + 1, 1, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x + 1, at_y - 1, 1, -1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x - 1, at_y + 1, -1, 1, color, ptr, tmp_steps);
    evaluate_post_move_for_bishop_queen
    (at_x, at_y, at_x - 1, at_y - 1, -1, -1, color, ptr, tmp_steps);
}

void Chess::reset()
{
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            if(m_figures[i][j]->get_figure() != EMPTY) {
                m_figures[i][j].reset(std::make_unique<Empty_figure>().release());
            }
        }
    }
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            if(i == 1) {
                m_figures[i][j] = std::make_unique<Pawn>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if(i == 6) {
                m_figures[i][j] = std::make_unique<Pawn>();
                m_figures[i][j]->set_collor(WHITE);
            }
            else if((i == 0 && j == 0) || (i == 0 && j == 7)) {
                m_figures[i][j] = std::make_unique<Rook>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if((i == 7 && j == 0) || (i == 7 && j == 7)) {
                m_figures[i][j] = std::make_unique<Rook>();
                m_figures[i][j]->set_collor(WHITE);
            }
            else if((i == 0 && j == 1) || (i == 0 && j == 6)) {
                m_figures[i][j] = std::make_unique<Knight>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if((i == 7 && j == 1) || (i == 7 && j == 6)) {
                m_figures[i][j] = std::make_unique<Knight>();
                m_figures[i][j]->set_collor(WHITE);
            }
            else if((i == 0 && j == 2) || (i == 0 && j == 5)) {
                m_figures[i][j] = std::make_unique<Bishop>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if((i == 7 && j == 2) || (i == 7 && j == 5)) {
                m_figures[i][j] = std::make_unique<Bishop>();
                m_figures[i][j]->set_collor(WHITE);
            }
            else if(i == 0 && j == 3) {
                m_figures[i][j] = std::make_unique<Queen>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if(i == 7 && j == 4) {
                m_figures[i][j] = std::make_unique<King>();
                m_figures[i][j]->set_collor(WHITE);
            }
            else if(i == 0 && j == 4) {
                m_figures[i][j] = std::make_unique<King>();
                m_figures[i][j]->set_collor(BLACK);
            }
            else if(i == 7 && j == 3) {
                m_figures[i][j] = std::make_unique<Queen>();
                m_figures[i][j]->set_collor(WHITE);
            }
        }
    }
}

void Chess::no_one_win()
{
    #ifdef _WIN32
    system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    std::cout << "No one WINs\n";
    std::cout << "PLAY AGAIN ?\n";
    std::cout << "YES  or NO\n";
    std::string answer{};
    std::cin >> answer;
    if(answer == "YES" || answer == "yes") {
        reset();
        play();
    }
    else {
        exit(0);
    }
}

void Chess::change_pawn(int x, int y)
{
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    if(turn == WHITE) {
        std::cout << "Choose the figure you want to change!\n";
        std::cout << "1. " << WHITE_QUEEN << "\n";
        std::cout << "2. " << WHITE_KNIGHT << "\n";
        std::cout << "3. " << WHITE_ROOK << "\n";
        std::cout << "4. " << WHITE_BISHOP << "\n";
        std::cout << "Input the number: ";
        char number{};
        std::cin >> number;
        while(number < '1' || number > '4') {
            std::cout << "Bad input! \n Try again :";
            std::cin >> number;
        }
        switch (number) {
            case '1':
                m_figures[x][y].reset(std::make_unique<Queen>().release());
                m_figures[x][y]->set_collor(WHITE);
                break;
            case '2':
                m_figures[x][y].reset(std::make_unique<Knight>().release());
                m_figures[x][y]->set_collor(WHITE);
                break;
            case '3':
                m_figures[x][y].reset(std::make_unique<Rook>().release());
                m_figures[x][y]->set_collor(WHITE);
                break;
            case '4':
                m_figures[x][y].reset(std::make_unique<Bishop>().release());
                m_figures[x][y]->set_collor(WHITE);
                break;
            default:
                break;
        }
    } else {
        std::cout << "Choose the figure you want to change!\n";
        std::cout << "1. " << BLACK_QUEEN << "\n";
        std::cout << "2. " << BLACK_KNIGHT << "\n";
        std::cout << "3. " << BLACK_ROOK << "\n";
        std::cout << "4. " << BLACK_BISHOP << "\n";
        std::cout << "Input the number: ";
        int number{};
        do {
            std::cin >> number;
        } while(!std::cin.good());
        switch (number) {
            case 1:
                m_figures[x][y].reset(std::make_unique<Queen>().release());
                m_figures[x][y]->set_collor(BLACK);
                break;
            case 2:
                m_figures[x][y].reset(std::make_unique<Knight>().release());
                m_figures[x][y]->set_collor(BLACK);
                break;
            case 3:
                m_figures[x][y].reset(std::make_unique<Rook>().release());
                m_figures[x][y]->set_collor(BLACK);
                break;
            case 4:
                m_figures[x][y].reset(std::make_unique<Bishop>().release());
                m_figures[x][y]->set_collor(BLACK);
                break;
            default:
                break;
        }
    }
    print();
}

void Chess::evaluate_post_move_for_king_pawn_knight
    (int at_x, int at_y, int to_x, int to_y, int x_direction, int y_direction,
    bool color, bool (Chess::*ptr)(int, int) const, const std::string& tmp_steps)
{
    if(verify_coordinates(to_x, to_y) &&
     ((m_figures[to_x][to_y]->get_figure() != EMPTY &&
     m_figures[to_x][to_y]->get_collor() != color) ||
     m_figures[to_x][to_y]->get_figure() == EMPTY)) {
        std::unique_ptr<Figure> tmp;
        tmp.reset(m_figures[to_x][to_y].release());
        m_figures[to_x][to_y].reset(m_figures[at_x][at_y].release());
        m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
        std::pair<int, int> king_pos = get_kings_position(color);
        if(!(this->*ptr)(king_pos.first, king_pos.second)) {
            std::string tmp = tmp_steps;
            tmp[0] += y_direction;
            tmp[1] += -x_direction;
            current_available_steps = tmp + current_available_steps;
            current_available_steps = " " + current_available_steps;
            ++all_available_steps_count;
        }
        m_figures[at_x][at_y].reset(m_figures[to_x][to_y].release());
        m_figures[to_x][to_y].reset(tmp.release());
    }
}

void Chess::evaluate_post_move_for_bishop_queen
    (int at_x, int at_y, int to_x, int to_y, int x_direction, int y_direction,
    bool color, bool (Chess::*ptr)(int, int) const, const std::string& tmp_steps)
{
    if(verify_coordinates(to_x, to_y)) {
        std::string tmp = tmp_steps;
        int i = to_x;
        int j = to_y;
        while((i < m_figures.size() && j < m_figures.size() && x_direction == 1 && y_direction == 1) || 
         (i < m_figures.size() && j >= 0 && x_direction == 1 && y_direction == -1) ||
         (i >= 0 && j < m_figures.size() && x_direction == -1 && y_direction == 1) ||
         (i >= 0 && j >= 0 && x_direction == -1 && y_direction == -1)) {
            if(m_figures[i][j]->get_figure() == EMPTY || 
            (m_figures[i][j]->get_figure() != EMPTY && 
            m_figures[i][j]->get_collor() != color)) {
                std::unique_ptr<Figure> tmpp;
                tmpp.reset(m_figures[i][j].release());
                m_figures[i][j].reset(m_figures[at_x][at_y].release());
                m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
                std::pair<int, int> king_pos = get_kings_position(color);
                if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                    tmp[0] = j + 'A';
                    tmp[1] = 8 - i + '0';
                    current_available_steps = tmp + current_available_steps;
                    current_available_steps = " " + current_available_steps;
                    ++all_available_steps_count;
                }
                m_figures[at_x][at_y].reset(m_figures[i][j].release());
                m_figures[i][j].reset(tmpp.release());
                if(m_figures[i][j]->get_figure() != EMPTY) {
                    break; 
                }
            }
            if(m_figures[i][j]->get_figure() != EMPTY && 
            m_figures[i][j]->get_collor() == color) {
                break;
            }
            if(x_direction == 1 && y_direction == 1) {
                ++i;
                ++j;
            } else if(x_direction == 1 && y_direction == -1) {
                ++i;
                --j;
            } else if(x_direction == -1 && y_direction == 1) {
                --i;
                ++j;
            } else if(x_direction == -1 && y_direction == -1) {
                --i;
                --j;
            }    
        }
    }
}

void Chess::evaluate_post_move_for_rook_queen
    (int at_x, int at_y, int to_x, int to_y, int x_direction, int y_direction,
    bool color, bool (Chess::*ptr)(int, int) const, const std::string& tmp_steps)
{
    if(verify_coordinates(to_x, to_y)) {
        std::string tmp = tmp_steps;
        int i = to_x;
        int j = to_y;
        while((i < m_figures.size() && x_direction == 1 && y_direction == 0) || 
         (i >= 0 && x_direction == -1 && y_direction == 0) ||
         (j < m_figures.size() && x_direction == 0 && y_direction == 1) ||
         (j >= 0 && x_direction == 0 && y_direction == -1)) {
            if(m_figures[i][j]->get_figure() == EMPTY || 
            (m_figures[i][j]->get_figure() != EMPTY && 
            m_figures[i][j]->get_collor() != color)) {
                std::unique_ptr<Figure> tmpp;
                tmpp.reset(m_figures[i][j].release());
                m_figures[i][j].reset(m_figures[at_x][at_y].release());
                m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
                std::pair<int, int> king_pos = get_kings_position(color);
                if(!(this->*ptr)(king_pos.first, king_pos.second)) {
                    tmp[0] = j + 'A';
                    tmp[1] = 8 - i + '0';
                    current_available_steps = tmp + current_available_steps;
                    current_available_steps = " " + current_available_steps;
                    ++all_available_steps_count;
                }
                m_figures[at_x][at_y].reset(m_figures[i][j].release());
                m_figures[i][j].reset(tmpp.release());
                if(m_figures[i][j]->get_figure() != EMPTY) {
                    break; 
                }
            }
            if(m_figures[i][j]->get_figure() != EMPTY && 
            m_figures[i][j]->get_collor() == color) {
                break;
            }
            if(x_direction == 1 && y_direction == 0) {
                ++i;
            } else if(x_direction == -1 && y_direction == 0) {
                --i;
            } else if(x_direction == 0 && y_direction == 1) {
                ++j;
            } else if(x_direction == 0 && y_direction == -1) {
                --j;
            }    
        }
    }
}

void Chess::empty_steps(int at_x, int at_y) {}

bool Chess::is_all_available_figures_are_kings() const
{
    int figures_count {};
    for(int i = 0; i < m_figures.size(); ++i) {
        for(int j = 0; j < m_figures[i].size(); ++j) {   
            if(m_figures[i][j]->get_figure() != EMPTY) {
                ++figures_count;
            }
        }
    }
    if(figures_count == 2) {
        return true;
    }
    return false;
}

std::pair<int, int> Chess::get_kings_position(bool color) const
{
    for(int i = 0; i < m_figures.size(); ++i) {
        for(int j = 0; j < m_figures[i].size(); ++j) {
            if(m_figures[i][j]->get_figure() == BLACK_KING && color == BLACK) {
                return std::make_pair(i, j);
            }
            else if(m_figures[i][j]->get_figure() == WHITE_KING && color == WHITE) {
                return std::make_pair(i, j);
            }
        }
    }
    return {};
}

bool Chess::is_king_attackable_by_pawn(int king_x, int king_y, bool color) const
{
    std::string pawn {};
    color == BLACK ? pawn = WHITE_PAWN: pawn = BLACK_PAWN;
    return ((verify_coordinates(king_x + 1, king_y - 1) && 
        (m_figures[king_x + 1][king_y - 1]->get_figure() == pawn)) ||
        (verify_coordinates(king_x + 1, king_y + 1) && 
        (m_figures[king_x + 1][king_y + 1]->get_figure() == pawn)));
}

bool Chess::is_king_attackable_by_knights(int king_x, int king_y, bool color) const
{
    std::string knight {};
    color == BLACK ? knight = WHITE_KNIGHT: knight = BLACK_KNIGHT;
    return ((verify_coordinates(king_x - 1, king_y - 2) && 
        (m_figures[king_x - 1][king_y - 2]->get_figure() == knight)) ||
        (verify_coordinates(king_x - 2, king_y - 1) && 
        (m_figures[king_x - 2][king_y - 1]->get_figure() == knight)) ||
        (verify_coordinates(king_x - 2, king_y + 1) && 
        (m_figures[king_x - 2][king_y + 1]->get_figure() == knight)) ||
        (verify_coordinates(king_x - 1, king_y + 2) && 
        (m_figures[king_x - 1][king_y + 2]->get_figure() == knight)) ||
        (verify_coordinates(king_x + 1, king_y + 2) && 
        (m_figures[king_x + 1][king_y + 2]->get_figure() == knight)) ||
        (verify_coordinates(king_x + 2, king_y + 1) && 
        (m_figures[king_x + 2][king_y + 1]->get_figure() == knight)) ||
        (verify_coordinates(king_x + 2, king_y - 1) && 
        (m_figures[king_x + 2][king_y - 1]->get_figure() == knight)) ||
        (verify_coordinates(king_x + 1, king_y - 2) && 
        (m_figures[king_x + 1][king_y - 2]->get_figure() == knight)));
}

bool Chess::is_king_attackable_by_rook_or_queen(int king_x, int king_y, bool color) const
{
    std::string rook {};
    std::string queen {};
    color == BLACK ? rook = WHITE_ROOK: rook = BLACK_ROOK;
    color == BLACK ? queen = WHITE_QUEEN: queen = BLACK_QUEEN;
    for(int i = king_x + 1; i < m_figures.size(); ++i) {
        if(m_figures[i][king_y]->get_figure() != EMPTY) {
            if(m_figures[i][king_y]->get_figure() == rook ||
            m_figures[i][king_y]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int i = king_x - 1; i >= 0; --i) {
        if(m_figures[i][king_y]->get_figure() != EMPTY) {
            if(m_figures[i][king_y]->get_figure() == rook ||
            m_figures[i][king_y]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int j = king_y + 1; j < m_figures.size(); ++j) {
        if(m_figures[king_x][j]->get_figure() != EMPTY) {
            if(m_figures[king_x][j]->get_figure() == rook ||
            m_figures[king_x][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int j = king_y - 1; j >= 0; --j) {
        if(m_figures[king_x][j]->get_figure() != EMPTY) {
            if(m_figures[king_x][j]->get_figure() == rook ||
            m_figures[king_x][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    return false;
}

bool Chess::is_king_attackable_by_bishop_or_queen(int king_x, int king_y, bool color) const
{
    std::string bishop {};
    std::string queen {};
    color == BLACK ? bishop = WHITE_BISHOP: bishop = BLACK_BISHOP;
    color == BLACK ? queen = WHITE_QUEEN: queen = BLACK_QUEEN;
    for(int i = king_x + 1, j = king_y + 1; i < m_figures.size() && j < m_figures[king_x].size(); ++i, ++j) {
        if(m_figures[i][j]->get_figure() != EMPTY) {
            if(m_figures[i][j]->get_figure() == bishop ||
                m_figures[i][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int i = king_x - 1, j = king_y + 1; i >= 0 && j < m_figures[king_x].size(); --i, ++j) {
        if(m_figures[i][j]->get_figure() != EMPTY) {
            if(m_figures[i][j]->get_figure() == bishop ||
                m_figures[i][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int i = king_x - 1, j = king_y - 1; i >= 0 && j >= 0; --i, --j) {
        if(m_figures[i][j]->get_figure() != EMPTY) {
            if(m_figures[i][j]->get_figure() == bishop ||
                m_figures[i][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    for(int i = king_x + 1, j = king_y - 1; i < m_figures.size() && j >= 0; ++i, --j) {
        if(m_figures[i][j]->get_figure() != EMPTY) {
            if(m_figures[i][j]->get_figure() == bishop ||
                m_figures[i][j]->get_figure() == queen) {
                return true;
            } else {
                break;
            }
        }
    }
    return false;
}

bool Chess::is_meeting_kings(int king_x, int king_y, bool color) const
{
    std::string king {};
    color == BLACK ? king = WHITE_KING: king = BLACK_KING;
    return ((verify_coordinates(king_x - 1, king_y - 1) && 
    m_figures[king_x - 1][king_y - 1]->get_figure() == king) ||
    (verify_coordinates(king_x - 1, king_y) && 
    m_figures[king_x - 1][king_y]->get_figure() == king) ||
    (verify_coordinates(king_x - 1, king_y + 1) && 
    m_figures[king_x - 1][king_y + 1]->get_figure() == king) ||
    (verify_coordinates(king_x, king_y - 1) && 
    m_figures[king_x][king_y - 1]->get_figure() == king) ||
    (verify_coordinates(king_x, king_y + 1) && 
    m_figures[king_x][king_y + 1]->get_figure() == king) ||
    (verify_coordinates(king_x - 1, king_y) && 
    m_figures[king_x - 1][king_y]->get_figure() == king) ||
    (verify_coordinates(king_x + 1, king_y - 1) && 
    m_figures[king_x + 1][king_y - 1]->get_figure() == king) ||
    (verify_coordinates(king_x + 1, king_y) && 
    m_figures[king_x + 1][king_y]->get_figure() == king) ||
    (verify_coordinates(king_x + 1, king_y + 1) && 
    m_figures[king_x + 1][king_y + 1]->get_figure() == king));
}

void Chess::play() 
{
    start();
    animation();
    turn = WHITE;
    end_game = false;
    all_passed_steps = "";
    do {
        print();
        input_coordinates();
    } while(!end_game);
}