#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <thread>
#include <chrono>

class Game
{
public:
    virtual void play() = 0;
    inline void animation() const;
    virtual ~Game() { }
};

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
    std::cout << tmp_anim << std::endl;
    if(counter % 5 == 0) {
        tmp_anim = "|" + tmp_anim;
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
}


#endif //GAME_H