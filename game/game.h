#ifndef GAME_H
#define GAME_H

class Game
{
public:
    virtual void play() = 0;
    inline virtual ~Game() = 0;
};

Game::~Game() {}

#endif //GAME_H