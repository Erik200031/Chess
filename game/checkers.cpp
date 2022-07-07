#include "checkers.h"

void Checkers::play() 
{

}

void Checkers::input_coordinates()
{
    std::string input;

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