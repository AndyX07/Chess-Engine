#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <vector>
#include <utility>
#include <unordered_map>

class Renderer;
namespace MoveGen { bool pawnPossible(int x,int y,int x1,int y1,bool pieceColor,char position[][8]); }
namespace Engine { std::pair<std::vector<int>, int> minimax(char position[][8], int depth, int alpha, int beta, bool maximizing_player); }

class Board
{
public:
    Board();
    virtual ~Board();

    void close();
    void generateBoard();
    void mouse(SDL_MouseButtonEvent e);
    void computerMove();

    bool possible(int x, int y, int x1, int y1, char c, bool inCheck, char position[][8]);
    bool getTurn();
    bool check(bool b, char position[][8]);
    bool checkMate(bool b);
    bool staleMate(bool b);

    void makeMove(int x, int y, int x1, int y1);
    void makeMoveP(char position[][8], int x1, int y1, int x2, int y2);
    void getAllMoves(bool b, char position[][8], std::vector<std::vector<int>> &ans);
    int eval(char position[][8]);

private:
    class Renderer* renderer = nullptr;
    char pieces[8][8];
    bool g[8][8];
    bool turn = true;
    int searchDepth = 3;
    bool isClosed = false;
};

#endif // BOARD_H
