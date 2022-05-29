#include "board.h"

Board::Board() : m_figures{}, m_height {DEFAULT_HEIGHT}, m_width {DEFAULT_WIDTH}
{
    m_figures.resize(m_height);
    for(int i = 0; i < m_figures.size(); ++i) {
        m_figures[i].resize(m_width);
    }
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            m_figures[i][j] = std::make_unique<Empty_figure>();
        }
    }
}

Board::Board(int height, int width) : m_figures{}, m_height {height}, m_width {width}
{
    m_figures.resize(m_height);
    for(int i = 0; i < m_figures.size(); ++i) {
        m_figures[i].resize(m_width);
    }
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            m_figures[i][j] = std::make_unique<Empty_figure>();
        }
    }
}

void Board::print() const
{
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            if(j == 0) { 
                std::cout << i + 1 << "| " << *m_figures[i][j] << " |";    
            } else {
                std::cout << "| " << *m_figures[i][j] << " |";  
            }  
        }
        std::string line (m_width * 5 - 2, '_');
        std::cout << "\n  " << line << '\n'; 
    }
}

const FIGURES& Board::get_figures() const 
{
    return m_figures;
}

