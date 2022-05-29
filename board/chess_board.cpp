#include "chess_board.h"

Chess_board::Chess_board()
{
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

void Chess_board::print() const
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