#include "Engine.h"
#include "MoveGen.h"
#include <climits>
#include <algorithm>
#include <chrono>
#include <random>

using namespace Engine;

int Engine::eval(char position[][8]){
    int score = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            char c = position[i][j];
            bool pieceColor = false;
            if(std::isupper(static_cast<unsigned char>(c))) pieceColor = true;
            char lower = std::tolower(static_cast<unsigned char>(c));
            if(lower=='p'){ if(pieceColor) score += 10; else score -= 10; }
            else if(lower=='r'){ if(pieceColor) score += 50; else score -= 50; }
            else if(lower=='n'){ if(pieceColor) score += 30; else score -= 30; }
            else if(lower=='b'){ if(pieceColor) score += 30; else score -= 30; }
            else if(lower=='k'){ if(pieceColor) score += 900; else score -= 900; }
            else if(lower=='q'){ if(pieceColor) score += 90; else score -= 90; }
        }
    }
    return score;
}

std::pair<std::vector<int>, int> Engine::minimax(char position[][8], int depth, int alpha, int beta, bool maximizing_player){
    if(depth == 0){
        return {{} , eval(position)};
    }
    std::vector<std::vector<int>> v;
    MoveGen::getAllMoves(maximizing_player, position, v);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
    std::vector<int> bestMove;
    if(maximizing_player){
        int maxEval = INT_MIN;
        for(auto &x : v){
            char originalPiece = position[x[2]][x[3]];
            MoveGen::makeMoveP(position, x[0], x[1], x[2], x[3]);
            auto p = minimax(position, depth-1, alpha, beta, false);
            int curEval = p.second;
            MoveGen::makeMoveP(position, x[2], x[3], x[0], x[1]);
            position[x[2]][x[3]] = originalPiece;
            if(curEval > maxEval){
                maxEval = curEval;
                bestMove = x;
            }
            alpha = std::max(alpha, curEval);
            if(beta <= alpha) break;
        }
        return {bestMove, maxEval};
    } else {
        int minEval = INT_MAX;
        for(auto &x : v){
            char originalPiece = position[x[2]][x[3]];
            MoveGen::makeMoveP(position, x[0], x[1], x[2], x[3]);
            auto p = minimax(position, depth-1, alpha, beta, true);
            int curEval = p.second;
            MoveGen::makeMoveP(position, x[2], x[3], x[0], x[1]);
            position[x[2]][x[3]] = originalPiece;
            if(curEval < minEval){
                minEval = curEval;
                bestMove = x;
            }
            beta = std::min(beta, curEval);
            if(beta <= alpha) break;
        }
        return {bestMove, minEval};
    }
}
