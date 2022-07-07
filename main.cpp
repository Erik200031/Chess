#include "game/game.h"
#include "game/chess.h"
#include "game/checkers.h"

#include <iostream>
#include <string>

int main() {
    Game* ptr = new Checkers();
    ptr->play();
    delete ptr;
   
}