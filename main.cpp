#include <iostream>
#include <string>
#include "game.h"
#include "chess.h"
#include <map>

int main() {
    Game* ptr = new Chess();
    ptr->play();
    delete ptr;

}