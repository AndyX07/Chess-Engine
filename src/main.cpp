#include "Board.h"
#include "MoveGen.h"
#include <iostream>

int main(int argc, char *argv[]){

    bool quit=false;
    SDL_Event e;
    Board cb;
    cb.generateBoard();
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                cb.mouse(e.button);
                bool turn = cb.getTurn();
                if (cb.checkMate(turn)) {
                    if (turn == 0) std::cout << "White Won" << std::endl;
                    else std::cout << "Black Won" << std::endl;
                    quit = true;
                }
                else if (cb.staleMate(turn)) {
                    std::cout << "Stalemate" << std::endl;
                    quit = true;
                }
            }
        }
        if (!cb.getTurn() && !quit) {
            cb.computerMove();

            bool turn = cb.getTurn();
            if (cb.checkMate(turn)) {
                if (turn == 0) std::cout << "White Won" << std::endl;
                else std::cout << "Black Won" << std::endl;
                quit = true;
            }
            else if (cb.staleMate(turn)) {
                std::cout << "Stalemate" << std::endl;
                quit = true;
            }
        }
    }
    cb.close();
    return 0;
}
