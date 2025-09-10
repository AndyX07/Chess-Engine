#include "MoveGen.h"
#include <cctype>
#include <utility>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace MoveGen;

bool MoveGen::getColor(int x, int y, char position[][8]){
    return std::isupper(position[x][y]);
}

void MoveGen::makeMoveP(char position[][8], int x1, int y1, int x2, int y2){
    if(position[x2][y2]=='a'){
        std::swap(position[x1][y1], position[x2][y2]);
    }
    else{
        position[x2][y2]='a';
        std::swap(position[x1][y1], position[x2][y2]);
    }
}


bool MoveGen::pawnPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    if(x1>=0&&y1>=0&&x1<8&&y1<8&&(x!=x1||y!=y1)){
        char c = position[x1][y1];
        if(!pieceColor){
            //black
            if(std::isupper(c)&&y1-y==1&&abs(x1-x)==1){
                return true;
            }
            if(y==1){
                if(x1==x){
                    if(y1-y==2&&c=='a'&&position[x][y1-1]=='a'){
                        return true;
                    }
                }
            }
            if(x1==x&&y1-y==1&&c=='a'){
                return true;
            }
        }
        else{
            //white
            if(std::islower(c)&&c!='a'&&y-y1==1&&abs(x1-x)==1){
                return true;
            }
            if(y==6){
                if(x1==x){
                    if(y-y1==2&&c=='a'&&position[x][y-1]=='a'){
                        return true;
                    }
                }
            }
            if(x1==x&&y-y1==1&&c=='a'){
                return true;
            }
        }
    }
    return false;
}

// Rook
bool MoveGen::rookPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    if(x1>=0&&y1>=0&&x1<8&&y1<8&&(x!=x1||y!=y1)){
        char c = position[x1][y1];
        if(x==x1){
            if(c=='a'||(!pieceColor&&std::isupper(c))||(pieceColor&&std::islower(c))){
                if(y1>y){
                    for(int i = y+1; i<y1; i++){
                        if(position[x][i]!='a') return false;
                    }
                    return true;
                }
                else{
                    for(int i = y-1; i>y1; i--){
                        if(position[x][i]!='a')return false;
                    }
                    return true;
                }
            }
        }
        if(y==y1){
            if(c=='a'||(!pieceColor&&std::isupper(c))||(pieceColor&&std::islower(c))){
                if(x1>x){
                    for(int i = x+1; i<x1; i++){
                        if(position[i][y]!='a') return false;
                    }
                    return true;
                }
                else{
                    for(int i = x-1; i>x1; i--){
                        if(position[i][y]!='a')return false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// Knight
bool MoveGen::knightPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    if(x1>=0&&y1>=0&&x1<8&&y1<8&&(x!=x1||y!=y1)){
        char c = position[x1][y1];
        if(c=='a'||(!pieceColor&&std::isupper(c))||(pieceColor&&std::islower(c))){
            if((abs(x-x1)==1&&abs(y-y1)==2)||(abs(x-x1)==2&&abs(y-y1)==1)){
                return true;
            }
        }
        return false;
    }
    return false;
}

// Bishop
bool MoveGen::bishopPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    if(x1>=0&&y1>=0&&x1<8&&y1<8&&(x!=x1||y!=y1)){
        if((pieceColor&&std::isupper(position[x1][y1])))return false;
        if((!pieceColor&&position[x1][y1]!='a'&&std::islower(position[x1][y1]))) return false;
        if(x+y==x1+y1 || x-x1==y-y1){
            int xc = (x1 > x) ? 1 : -1;
            int yc = (y1 > y) ? 1 : -1;
            int i = x, j = y;
            while(0<=i && 0<=j && i<=7 && j<=7){
                i += xc;
                j += yc;
                if(x1==i && y1==j) return true;
                if(position[i][j] != 'a') return false;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

// Queen
bool MoveGen::queenPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    return bishopPossible(x,y,x1,y1,pieceColor,position) || rookPossible(x,y,x1,y1,pieceColor,position);
}

// King
bool MoveGen::kingPossible(int x, int y, int x1, int y1, bool pieceColor, char position[][8]){
    if(x1>=0&&y1>=0&&x1<8&&y1<8){
        if(position[x1][y1]=='a'||pieceColor!=getColor(x1, y1, position)){
            int d1 = abs(x-x1);
            int d2 = abs(y-y1);
            if((d1==0&&d2==1) || (d1==1&&d2==0) || (d1==1&&d2==1)) return true;
            else return false;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool MoveGen::possible(int x, int y, int x1, int y1, char c, bool m, char position[][8]){
    bool pieceColor = std::isupper(c);
    bool res = false;
    char originalPiece = position[x1][y1];
    char lower = std::tolower(c);
    if(lower=='p') res = pawnPossible(x,y,x1,y1,pieceColor,position);
    else if(lower=='r') res = rookPossible(x,y,x1,y1,pieceColor,position);
    else if(lower=='n') res = knightPossible(x,y,x1,y1,pieceColor,position);
    else if(lower=='b') res = bishopPossible(x,y,x1,y1,pieceColor,position);
    else if(lower=='k') res = kingPossible(x,y,x1,y1,pieceColor,position);
    else if(lower=='q') res = queenPossible(x,y,x1,y1,pieceColor,position);

    if(!m) return res;
    if(!res) return false;

    makeMoveP(position, x, y, x1, y1); // temporarily make move
    if(check(pieceColor, position)){
        // undo
        makeMoveP(position, x1, y1, x, y);
        position[x1][y1] = originalPiece;
        return false;
    }
    // undo
    makeMoveP(position, x1, y1, x, y);
    position[x1][y1] = originalPiece;
    return true;
}

void MoveGen::getAllMoves(bool pieceColor, char position[][8], std::vector<std::vector<int>> &ans){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    if(std::make_pair(i, j) != std::make_pair(k, l) && position[i][j] != 'a' && getColor(i, j, position) == pieceColor && possible(i, j, k, l, position[i][j], true, position)){
                        ans.push_back({i, j, k, l});
                    }
                }
            }
        }
    }
}

bool MoveGen::check(bool pieceColor, char position[][8]){
    int x=-1, y=-1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(std::tolower(position[i][j])=='k' && getColor(i,j,position) == pieceColor){
                x = i; y = j;
                break;
            }
        }
        if(x!=-1) break;
    }
    if(x==-1) return false;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==x && j==y) continue;
            if(position[i][j] != 'a'){
                if(possible(i, j, x, y, position[i][j], false, position)) return true;
            }
        }
    }
    return false;
}

bool MoveGen::checkMate(bool pieceColor, char position[][8]){
    if(!check(pieceColor, position)) return false;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(position[i][j] != 'a' && getColor(i,j,position)==pieceColor){
                for(int k=0;k<8;k++){
                    for(int l=0;l<8;l++){
                        if(possible(i,j,k,l,position[i][j], true, position)) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool MoveGen::staleMate(bool pieceColor, char position[][8]){
    if(check(pieceColor, position)) return false;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(position[i][j] != 'a' && getColor(i,j,position)==pieceColor){
                for(int k=0;k<8;k++){
                    for(int l=0;l<8;l++){
                        if(possible(i,j,k,l,position[i][j], true, position)) return false;
                    }
                }
            }
        }
    }
    return true;
}
