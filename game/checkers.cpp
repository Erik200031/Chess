#include "checkers.h"

void Checkers::play() 
{
    m_turn = WHITE;
    print();
    input_coordinates();
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
    int at_x = m_figures.size() - 1 - parsed.second + 1;
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
        return std::make_pair(input[0] - 65, std::stoi(input.substr(1,2)));
    }
    return std::make_pair(-1, -1);
}

void Checkers::view_current_available_steps(int at_x, int at_y)
{
    current_available_steps = "";
    if(m_figures[at_x][at_y]->get_figure() == WHITE_FIGURE &&
    verify_coordinates(at_x - 1, at_y - 1) && 
    m_figures[at_x - 1][at_y - 1]->get_figure() == EMPTY) {
        current_available_steps += "   "; //3 space for edit chars
        current_available_steps[current_available_steps.size() - 2]
        = at_x - 1;
        current_available_steps[current_available_steps.size() - 2]
        = at_y - 1;
        std::cout << current_available_steps << "<-";
    }
}