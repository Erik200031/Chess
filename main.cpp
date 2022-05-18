#include "game.h"
#include "chess.h"

int main() {
    Game* ptr = new Chess();
    ptr->play();
    delete ptr;
}