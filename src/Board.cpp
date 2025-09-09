#include "Board.h"
#include "Renderer.h"
#include "MoveGen.h"
#include "Engine.h"
#include <SDL_image.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

Board::Board() {
    std::memset(g, 0, sizeof(g));
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) pieces[i][j] = 'a';
    pieces[0][0]='r'; pieces[1][0]='n'; pieces[2][0]='b'; pieces[3][0]='q';
    pieces[4][0]='k'; pieces[5][0]='b'; pieces[6][0]='n'; pieces[7][0]='r';
    for(int i = 0; i < 8; i++){ pieces[i][1]='p'; pieces[i][6]='P'; }
    pieces[0][7]='R'; pieces[1][7]='N'; pieces[2][7]='B'; pieces[3][7]='Q';
    pieces[4][7]='K'; pieces[5][7]='B'; pieces[6][7]='N'; pieces[7][7]='R';

    renderer = new Renderer();
    if(!renderer->init()){
        std::cerr << "SDL init failed\n";
    }
    renderer->setBoardRef(pieces);
    renderer->setHighlights(g);
    renderer->loadPieceImages("../images/");
}

Board::~Board() {
    close();
    delete renderer;
}

void Board::close(){
    if (isClosed) return;
    if(renderer) renderer->close();
    isClosed = true;
}

void Board::generateBoard(){
    if(renderer) renderer->generateBoard();
}

void Board::makeMove(int x, int y, int x1, int y1){
    if(pieces[x1][y1]=='a'){
        std::swap(pieces[x][y], pieces[x1][y1]);
    } else {
        pieces[x1][y1] = 'a';
        std::swap(pieces[x][y], pieces[x1][y1]);
    }
}

void Board::makeMoveP(char position[][8], int x1, int y1, int x2, int y2) {
    MoveGen::makeMoveP(position, x1, y1, x2, y2);
}

bool Board::possible(int x, int y, int x1, int y1, char c, bool inCheck, char position[][8]) {
    return MoveGen::possible(x,y,x1,y1,c,inCheck,position);
}

bool Board::getTurn(){ return turn; }

bool Board::check(bool b, char position[][8]) {
    return MoveGen::check(b, position);
}

bool Board::checkMate(bool b) {
    return MoveGen::checkMate(b, pieces);
}

bool Board::staleMate(bool b) {
    return MoveGen::staleMate(b, pieces);
}

void Board::getAllMoves(bool b, char position[][8], std::vector<std::vector<int>> &ans) {
    MoveGen::getAllMoves(b, position, ans);
}

int Board::eval(char position[][8]) {
    return Engine::eval(position);
}

void Board::mouse(SDL_MouseButtonEvent e){
    if(turn){
        bool ismove = false;
        int x = e.x/75;
        int y = e.y/75;
        if(x < 0 || x > 7 || y < 0 || y > 7) return;
        if(pieces[x][y]!='a'){
            if(MoveGen::getColor(x, y, pieces) == turn){
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        if(possible(x, y, i, j, pieces[x][y], 1, pieces)){
                            g[i][j]=1;
                            ismove = true;
                        } else g[i][j]=0;
                    }
                }
                if(!ismove) return;
                renderer->generateBoard();
                SDL_Event ev;
                bool quitLoop = false;
                while(!quitLoop){
                    while(SDL_PollEvent(&ev)!=0){
                        if(ev.type==SDL_MOUSEBUTTONUP){
                            int x1 = ev.button.x/75;
                            int y1 = ev.button.y/75;
                            if(x1 < 0 || x1>7 || y1<0 || y1>7) { quitLoop = true; break; }
                            if(g[x1][y1]){
                                makeMove(x, y, x1, y1);
                                std::memset(g, 0, sizeof(g));
                                if(y1==0 && pieces[x1][y1]=='P') pieces[x1][y1]='Q';
                                if(y1==7 && pieces[x1][y1]=='p') pieces[x1][y1]='q';
                                renderer->generateBoard();
                                quitLoop = true;
                                turn = !turn;
                                break;
                            } else {
                                std::memset(g, 0, sizeof(g));
                                renderer->generateBoard();
                                return;
                            }
                        }
                        usleep(10000);
                    }
                }
            }
        }
    }
}

void Board::computerMove(){
    if(!turn){
        auto p = Engine::minimax(pieces, searchDepth, INT_MIN, INT_MAX, 0);
        if(p.first.size() >= 4){
            makeMove(p.first[0], p.first[1], p.first[2], p.first[3]);
            if(p.first[3]==0 && pieces[p.first[2]][p.first[3]]=='P') pieces[p.first[2]][p.first[3]]='Q';
            if(p.first[3]==7 && pieces[p.first[2]][p.first[3]]=='p') pieces[p.first[2]][p.first[3]]='q';
            turn = !turn;
            renderer->generateBoard();
        }
    }
}
