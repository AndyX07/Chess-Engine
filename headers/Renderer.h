#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <unordered_map>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init();
    void close();

    void setBoardRef(char board[8][8]);
    void setHighlights(bool g[8][8]);

    void generateBoard();
    void loadPieceImages(const char* basePath = "../images/");

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unordered_map<char, SDL_Surface*> pieceImages;

    SDL_Color brown;
    SDL_Color white;
    SDL_Color green;

    static constexpr int SCREEN_H = 600;
    static constexpr int SCREEN_W = 600;
    static constexpr int TILE_SIZE = 75;
    static constexpr int PIECE_SIZE = 60;

    char (*board)[8] = nullptr;
    bool (*highlights)[8] = nullptr;

    void drawRect(SDL_Color c, int x1, int y1, int w, int h);
    void placePiece(SDL_Surface* img, int x, int y, int w, int h);
};

#endif // RENDERER_H
