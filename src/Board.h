#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <vector>
#include <utility>
#include <unordered_map>

class Board
{
    public:
        Board();
        virtual ~Board();

        void close();
        void drawRect(SDL_Color c, int x1, int y1, int w, int h);
        void placePiece(SDL_Surface* img, int x, int y, int w, int h);
        void generateBoard();

        bool possible(int x, int y, int x1, int y1, char c, bool inCheck, char position[][8]);
        char getPiece(int x, int y);
        void setPiece(int x, int y, char c);

        bool pawnPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
        bool rookPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
        bool knightPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
        bool bishopPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
        bool queenPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
        bool kingPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);

        bool check(bool b, char position[][8]);
        bool checkMate(bool b);
        bool staleMate(bool b);
        bool getColor(int x, int y, char position[][8]);

        void mouse(SDL_MouseButtonEvent e);
        void makeMove(int x, int y, int x1, int y1);
        void movePiece(int x, int y, int x1, int y1);
        void resetG();

        int eval(char position[][8]);
        void computerMove();

        void makeMoveP(char position[][8], int x1, int y1, int x2, int y2);
        void getAllMoves(bool b, char position[][8], std::vector<std::vector<int>>& ans);
        std::pair<std::vector<int>, int> minimax(char position[][8], int depth, int alpha, int beta, bool maximizing_player);

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Color brown;
        SDL_Color white;
        SDL_Color green;

        static constexpr int SCREEN_H = 600;
        static constexpr int SCREEN_W = 600;

        char pieces[8][8];
        bool g[8][8];
        bool turn = true;
        int searchDepth = 3;
        bool isClosed = false;

        std::unordered_map<char, SDL_Surface*> pieceImages;
};

#endif // BOARD_H
