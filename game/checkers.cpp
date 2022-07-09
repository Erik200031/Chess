#include "checkers.h"

void Checkers::play() 
{
    start();
    animation();
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    std::cout << "DO YOU WANT THE GAME TO BE WITH BACK EATING?\n";
    std::cout << "YES / NO : ";
    std::string input{};
    std::cin >> input;
    if(input == "Y" || input == "Yes" ||
     input == "YES" || input == "yes" || input == "y") {
        m_back_eat_flag = true;
    } else {m_back_eat_flag = false;}
    m_turn = WHITE;
    print();
    while (true)
    {
        input_coordinates();
    }
    
}

void Checkers::input_coordinates()
{
    std::string at_input;
checker:
    print();
    m_turn == WHITE ? std::cout << "\nTURN -> WHITE\n" : std::cout <<  "\nTURN -> BLACK\n";
    std::cout << "\nAt: ";
    std::cin >> at_input;
    at_input[0] = toupper(at_input[0]);
    auto parsed = parse_input(at_input);
    while(parsed.first == -1) {
        print();
        std::cout << "\nBad input! Try again\n";
        std::cout << "\nAt: ";
        std::cin >> at_input;
        at_input[0] = toupper(at_input[0]);
        parsed = parse_input(at_input);
    }
    int at_y = parsed.first;
    int at_x = m_figures.size() - parsed.second;
    if(m_turn == WHITE && (m_figures[at_x][at_y]->get_figure() != EMPTY && 
     m_figures[at_x][at_y]->get_figure() == BLACK_FIGURE || 
     m_figures[at_x][at_y]->get_figure() == BLACK_QUEEN) || 
     m_figures[at_x][at_y]->get_figure() == EMPTY) {
        goto checker;
    } else if(m_turn == BLACK && (m_figures[at_x][at_y]->get_figure() != EMPTY && 
     m_figures[at_x][at_y]->get_figure() == WHITE_FIGURE || 
     m_figures[at_x][at_y]->get_figure() == WHITE_QUEEN) || 
     m_figures[at_x][at_y]->get_figure() == EMPTY) {
        goto checker;
    }
    view_current_available_steps(at_x, at_y);
    if(current_available_steps.size() == 0) {
        using namespace std::chrono_literals;
        std::cout << "No available steps\n";
        std::this_thread::sleep_for(800ms);
        goto checker;
    }
    std::cout << "Available steps -> " << current_available_steps;
    std::cout << "\nTo: ";
    std::string to_input{};
    std::cin >> to_input;
    to_input[0] = toupper(to_input[0]);
    parsed = parse_input(to_input);
    while(parsed.first == -1) {
        print();
        std::cout << "\nBad input! Try again\n";
        if(current_available_steps.size() <= 2) {
            std::cout << "No available steps! ";
        } else {
            std::cout << "Available steps -> " << current_available_steps;
        }
    }
    int to_y = parsed.first;
    int to_x = m_figures.size() - parsed.second;



    m_figures[to_x][to_y].reset(m_figures[at_x][at_y].release());
    m_figures[at_x][at_y] = std::make_unique<Empty_figure>();
    m_turn == BLACK ? m_turn = WHITE: m_turn = BLACK;
}

bool Checkers::verify_coordinates(int x, int y) const 
{
    return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

std::pair<int, int> Checkers::parse_input(const std::string& input)
{
    if(input.size() <= 1 || input.size() > 2) {
        return std::make_pair(-1, -1);
    }
    else if(((input[0] - 65 >= 0) && (input[0] - 65 <= 7)) &&
     (input[1] >= '1') && (input[1] <= '8')) {
        return std::make_pair(input[0] - 'A', std::stoi(input.substr(1,2)));
    }
    return std::make_pair(-1, -1);
}

void Checkers::view_current_available_steps(int at_x, int at_y)
{
    view_current_available_steps_left_non_queen(at_x, at_y);
}

void Checkers::view_current_available_steps_left_non_queen(int at_x, int at_y)
{
    current_available_steps = "";
    std::string tmp_figure;
    std::string enemy_figure;
    std::string enemy_queen;
    int direction;
    if(m_figures[at_x][at_y]->get_figure() == WHITE_FIGURE) {
        tmp_figure = WHITE_FIGURE;
        enemy_figure = BLACK_FIGURE;
        enemy_queen = BLACK_QUEEN;
        direction = 1;
    } else {
        tmp_figure = BLACK_FIGURE;
        enemy_figure = WHITE_FIGURE;
        enemy_queen = WHITE_QUEEN;
        direction = -1;
    }
    if(m_figures[at_x][at_y]->get_figure() == tmp_figure &&
     verify_coordinates(at_x - 1 * direction, at_y - 1) && 
    m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == EMPTY) {
        /* 3 space for edit chars */
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 1;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' + 1 * direction;
    }
    else if(m_figures[at_x][at_y]->get_figure() == tmp_figure && 
     verify_coordinates(at_x - 1 * direction, at_y - 1) && 
     (m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == enemy_figure ||
     m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == enemy_queen) && 
     (verify_coordinates(at_x - 2 * direction, at_y - 2))) {
        /* 3 space for edit chars */
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 2;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' + 2 * direction; 
    }
    if(m_back_eat_flag && (m_figures[at_x][at_y]->get_figure() == tmp_figure && 
     verify_coordinates(at_x + 1 * direction, at_y - 1) && 
     (m_figures[at_x + 1 * direction][at_y - 1]->get_figure() == enemy_figure ||
     m_figures[at_x + 1 * direction][at_y - 1]->get_figure() == enemy_queen)) && 
     (verify_coordinates(at_x + 2 * direction, at_y - 2))) {
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 2;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' - 2 * direction;
    }
}

void Checkers::view_current_available_steps_left_non_queen_helper
 (int at_x, int at_y)
{

}

void Checkers::view_current_available_steps_right_non_queen(int at_x, int at_y)
{
    current_available_steps = "";
    std::string tmp_figure;
    std::string enemy_figure;
    std::string enemy_queen;
    int direction;
    if(m_figures[at_x][at_y]->get_figure() == WHITE_FIGURE) {
        tmp_figure = WHITE_FIGURE;
        enemy_figure = BLACK_FIGURE;
        enemy_queen = BLACK_QUEEN;
        direction = 1;
    } else {
        tmp_figure = BLACK_FIGURE;
        enemy_figure = WHITE_FIGURE;
        enemy_queen = WHITE_QUEEN;
        direction = -1;
    }
    if(m_figures[at_x][at_y]->get_figure() == tmp_figure &&
     verify_coordinates(at_x - 1 * direction, at_y - 1) && 
    m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == EMPTY) {
        /* 3 space for edit chars */
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 1;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' + 1 * direction;
    }
    else if(m_figures[at_x][at_y]->get_figure() == tmp_figure && 
     verify_coordinates(at_x - 1 * direction, at_y - 1) && 
     (m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == enemy_figure ||
     m_figures[at_x - 1 * direction][at_y - 1]->get_figure() == enemy_queen) && 
     (verify_coordinates(at_x - 2 * direction, at_y - 2))) {
        /* 3 space for edit chars */
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 2;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' + 2 * direction; 
    }
    if(m_back_eat_flag && (m_figures[at_x][at_y]->get_figure() == tmp_figure && 
     verify_coordinates(at_x + 1 * direction, at_y - 1) && 
     (m_figures[at_x + 1 * direction][at_y - 1]->get_figure() == enemy_figure ||
     m_figures[at_x + 1 * direction][at_y - 1]->get_figure() == enemy_queen)) && 
     (verify_coordinates(at_x + 2 * direction, at_y - 2))) {
        current_available_steps += "   ";                       
        current_available_steps[current_available_steps.size() - 2]
        = at_y + 'A' - 2;
        current_available_steps[current_available_steps.size() - 1]
        = 8 - at_x + '0' - 2 * direction;
    }
}