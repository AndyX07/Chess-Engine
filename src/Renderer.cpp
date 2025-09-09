#include "Renderer.h"
#include <SDL_image.h>
#include <cstring>

Renderer::Renderer() {
    brown = {168, 117, 50, 255};
    white = {255, 255, 255, 255};
    green = {32, 252, 3, 255};
}

Renderer::~Renderer() {
    close();
}

bool Renderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    window = SDL_CreateWindow("CHESS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) return false;
    return true;
}

void Renderer::loadPieceImages(const char* basePath) {
    pieceImages['p'] = IMG_Load((std::string(basePath)+ "bpawn.png").c_str());
    pieceImages['P'] = IMG_Load((std::string(basePath)+ "wpawn.png").c_str());
    pieceImages['r'] = IMG_Load((std::string(basePath)+ "brook.png").c_str());
    pieceImages['R'] = IMG_Load((std::string(basePath)+ "wrook.png").c_str());
    pieceImages['n'] = IMG_Load((std::string(basePath)+ "bknight.png").c_str());
    pieceImages['N'] = IMG_Load((std::string(basePath)+ "wknight.png").c_str());
    pieceImages['b'] = IMG_Load((std::string(basePath)+ "bbishop.png").c_str());
    pieceImages['B'] = IMG_Load((std::string(basePath)+ "wbishop.png").c_str());
    pieceImages['q'] = IMG_Load((std::string(basePath)+ "bqueen.png").c_str());
    pieceImages['Q'] = IMG_Load((std::string(basePath)+ "wqueen.png").c_str());
    pieceImages['k'] = IMG_Load((std::string(basePath)+ "bking.png").c_str());
    pieceImages['K'] = IMG_Load((std::string(basePath)+ "wking.png").c_str());
}

void Renderer::close() {
    for (auto &p : pieceImages) {
        if (p.second) {
            SDL_FreeSurface(p.second);
            p.second = nullptr;
        }
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}

void Renderer::setBoardRef(char b[8][8]) {
    board = b;
}
void Renderer::setHighlights(bool h[8][8]) {
    highlights = h;
}

void Renderer::drawRect(SDL_Color c, int x1, int y1, int w, int h) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Rect rect = {x1, y1, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::placePiece(SDL_Surface* img, int x, int y, int w, int h) {
    if (!img) return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
    if(!texture) return;
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void Renderer::generateBoard() {
    if (!renderer || !board) return;
    SDL_RenderClear(renderer);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (highlights && highlights[i][j])
                drawRect(green, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            else if ((i + j) % 2 == 0)
                drawRect(white, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            else
                drawRect(brown, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char c = board[i][j];
            if (c != 'a') {
                SDL_Surface* img = pieceImages[c];
                if (img) placePiece(img, i * TILE_SIZE + 5, j * TILE_SIZE + 5, PIECE_SIZE, PIECE_SIZE);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
