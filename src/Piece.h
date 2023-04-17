#ifndef PIECE_H
#define PIECE_H


class Piece
{
    public:
        Piece();
        bool pawnPossible(int x, int y, int x1, int y1, bool b);
        bool rookPossible(int x, int y, int x1, int y1, bool b);
        bool knightPossible(int x, int y, int x1, int y1, bool b);
        bool bishopPossible(int x, int y, int x1, int y1, bool b);;
        bool queenPossible(int x, int y, int x1, int y1, bool b);
        bool kingPossible(int x, int y, int x1, int y1, bool b);
        virtual ~Piece();

    protected:

    private:
};

#endif // PIECE_H
