#pragma once
#include<string>
#include<vector>
#include<SDL.h>

struct Coordenadas
{
    int x;
    int y;
};

// Overload the * operator for Coordenadas and int
inline Coordenadas operator*(const Coordenadas& coord, const int scalar) {
    return Coordenadas{coord.x * scalar, coord.y * scalar};
}

// Overload the + operator for Coordenadas
inline Coordenadas operator+(const Coordenadas& lhs, const Coordenadas& rhs) {
    return Coordenadas{lhs.x + rhs.x, lhs.y + rhs.y};
}

// Overload the + operator for Coordenadas
inline Coordenadas operator-(const Coordenadas& lhs, const Coordenadas& rhs) {
    return Coordenadas{lhs.x - rhs.x, lhs.y - rhs.y};
}

struct AtlasInfo
{
    int tile_width;
    int tile_height;
    std::vector<std::vector<int>> mapa_ids;
    std::string archivo_ids;
    std::string archivo_atlas;
    int renglones;
    int columnas;
    int num_tiles_ancho;
    int num_tiles_alto;
    int atlas_width;
    int atlas_height;
};

struct TileInfo
{
    SDL_RendererFlip flip;
    double angulo;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_Texture *source;
    Coordenadas pos;
    int width;
    int height;
};