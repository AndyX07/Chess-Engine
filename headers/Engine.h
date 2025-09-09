#ifndef Engine_H
#define Engine_H

#include <vector>
#include <utility>

namespace Engine {
    int eval(char position[][8]);
    std::pair<std::vector<int>, int> minimax(char position[][8], int depth, int alpha, int beta, bool maximizing_player);
}

#endif
