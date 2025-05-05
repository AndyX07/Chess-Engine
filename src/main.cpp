#include "SDL.h"
#include "Board.h"
#include "SDL_image.h"

using namespace std;

int main(int argc, char *argv[]){

    bool quit=0;
    SDL_Event e;
    Board cb = Board();
    cb.generateBoard();
    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if(e.type==SDL_QUIT){
                quit=1;
            }
            else if(e.type==SDL_MOUSEBUTTONUP){
                cb.mouse(e.button);
            }
        }
        if(cb.checkMate(1)){
            cout << "Black Won" << endl;
            quit = 1;
        }
        if(cb.checkMate(0)){
            cout << "White Won" << endl;
            quit = 1;
        }
        if(cb.staleMate(1)||cb.staleMate(0)){
            cout << "Stalemate" << endl;
            quit = 1;
        }
        cb.computerMove();
    }
    cb.close();
    return 0;
}
