#include "SDL.h"
#include "Board.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    bool quit=0;
    SDL_Event e;
    Board cb = Board();
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
                    if (turn == 0) cout << "White Won" << endl;
                    else cout << "Black Won" << endl;
                    quit = true;
                }
                else if (cb.staleMate(turn)) {
                    cout << "Stalemate" << endl;
                    quit = true;
                }
            }
        }
        if (!cb.getTurn() && !quit) {
            cb.computerMove();

            bool turn = cb.getTurn();
            if (cb.checkMate(turn)) {
                if (turn == 0) cout << "White Won" << endl;
                else cout << "Black Won" << endl;
                quit = true;
            }
            else if (cb.staleMate(turn)) {
                cout << "Stalemate" << endl;
                quit = true;
            }
        }
    }
    cb.close();
    return 0;
}
