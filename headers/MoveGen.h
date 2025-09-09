#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>

namespace MoveGen {
    bool pawnPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
    bool rookPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
    bool knightPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
    bool bishopPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
    bool queenPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);
    bool kingPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]);

    bool possible(int x, int y, int x1, int y1, char c, bool m, char position[][8]);
    bool getColor(int x, int y, char position[][8]);

    void makeMoveP(char position[][8], int x1, int y1, int x2, int y2);
    void getAllMoves(bool pieceColor, char position[][8], std::vector<std::vector<int>> &ans);

    bool check(bool pieceColor, char position[][8]);
    bool checkMate(bool pieceColor, char position[][8]);
    bool staleMate(bool pieceColor, char position[][8]);
}

#endif // MOVEGEN_H
