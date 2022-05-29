#include "game/game.h"
#include "game/chess.h"

int main() {
    Game* ptr = new Chess();
    ptr->play();
    delete ptr;
}