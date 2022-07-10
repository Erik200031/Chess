#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"     
#define RESET   "\033[0m"

class Game
{
public:
    virtual void play() = 0;
    inline void start() const;
    inline void animation() const;
    virtual ~Game() = default;
};

void Game::start() const
{
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif    
    std::cout << "______________________________\n";
    std::cout << "__________GAME STARTED________\n";
    std::cout << "------------------------------\n\n";
    int ch;
    std::cout << RED << " 0.EXIT\n" << GREEN <<" 1.CONTINUE\n "<<
    RESET << " \nEnter your choice:  _\b";
    std::cin >> ch;
    if(!std::cin.good()) {
        std::cout << "ERROR Undefined Input!!\n";
        exit(0);
    }
    if(ch == 0) {
        exit(0);
    }
}

void Game::animation() const
{
    int i = 0;
    using namespace std::chrono_literals;
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    int counter {};
    std::string tmp_anim = "|";
    std::string tmp_anim2 = "|";
label0:
    if(counter == 100) {
        goto lbl4;
    }
    std::this_thread::sleep_for(20ms);
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    goto label1;
label1:
    ++counter;
    std::cout << "\n\n";
    std::cout << "LOADING\n\n";
    std::cout << "____________________\n";
    if(counter < 33) {
        std::cout << RED << tmp_anim << std::endl;
    } else if(counter >= 33 && counter <= 66) {
        std::cout << YELLOW << tmp_anim << std::endl;
    } else if(counter > 66) {
        std::cout << GREEN << tmp_anim << std::endl;
    }
    if(counter < 33) {
        std::cout << RED << tmp_anim2 << std::endl;
    } else if(counter >= 33 && counter <= 66) {
        std::cout << YELLOW << tmp_anim2 << std::endl;
    } else if(counter > 66) {
        std::cout << GREEN << tmp_anim2 << std::endl;
    }
    std::cout << "____________________";
    if(counter % 5 == 0) {
        tmp_anim = "|" + tmp_anim;
        tmp_anim2 = "|" + tmp_anim2;
        goto lbltmp;
    }
lbltmp:
    std::cout << '\n';
    std::cout << i << "%\n";
    ++i;
        goto label0;
lbl4:
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        system("cls");    
    #else 
        system("clear");
    #endif
    std::cout << RESET;
}

#endif //GAME_H