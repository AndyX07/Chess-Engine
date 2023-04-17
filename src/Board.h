#ifndef BOARD_H
#define BOARD_H

#include "SDL.h"
#include <bits/stdc++.h>

using namespace std;

class Board
{
    public:
        Board();
        void close();
        void drawRect(SDL_Color c, int x1, int y1, int w, int h);
        void placePiece(SDL_Surface *img, int x, int y, int w, int h);
        void generateBoard();
        bool possible(int x, int y, int x1, int y1, char c, bool inCheck, char position[][8]);
        char getPiece(int x, int y);
        void setPiece(int x, int y, char c);
        bool pawnPossible(int x, int y, int x1, int y1, bool b, char position[][8]);
        bool rookPossible(int x, int y, int x1, int y1, bool b, char position[][8]);
        bool knightPossible(int x, int y, int x1, int y1, bool b, char position[][8]);
        bool bishopPossible(int x, int y, int x1, int y1, bool b, char position[][8]);;
        bool queenPossible(int x, int y, int x1, int y1, bool b, char position[][8]);
        bool kingPossible(int x, int y, int x1, int y1, bool b, char position[][8]);
        bool check(bool b, char position[][8]);
        bool checkMate(bool b);
        bool getColor(int x, int y, char position[][8]);
        void mouse(SDL_MouseButtonEvent e);
        void makeMove(int x, int y, int x1, int y1);
        void movePiece(int x, int y, int x1, int y1);
        void resetG();
        bool staleMate(bool b);
        int eval(char position[][8]);
        void computerMove();
        void makeMoveP(char position[][8], int x1, int y1, int x2, int y2);
        void getAllMoves(bool b, char position[][8], vector<vector<int>> &ans);
        pair<vector<int>, int> minimax(char position[][8], int depth, int alpha, int beta, bool maximizing_player);
        virtual ~Board();

    protected:

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Color brown;
        SDL_Color white;
        SDL_Color green;
        const int SCREEN_H = 600;
        const int SCREEN_W = 600;
        char pieces[8][8];
        bool g[8][8];
        bool turn = 1;
        int searchDepth = 3;
};

#endif // BOARD_H
