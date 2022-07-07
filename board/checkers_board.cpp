#include "checkers_board.h"

Checkers_board::Checkers_board()
{
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            if((i + j) % 2 != 0 && i < 3) {
                m_figures[i][j] = std::make_unique<Checker_figure>();
            }
            else if((i+j)%2!=0 && i>4){
                m_figures[i][j] = std::make_unique<Checker_figure>();
                m_figures[i][j]->set_collor(WHITE);
            }
        }
    }
}

void Checkers_board::print() const
{
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    std::cout<<"  _A____B____C____D____E____F____G____H__\n";
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            if(j == 0) { 
                std::cout << m_height - i << "| " << *m_figures[i][j] << " |";    
            } else {
                std::cout << "| " << *m_figures[i][j] << " |";  
            }  
        }
        std::string line (m_width * 5 - 2, '_');
        std::cout << "\n  " << line << '\n'; 
    }
}