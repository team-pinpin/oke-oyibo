#pragma once

#include "world/Tile.h"

namespace world
{
    class Terrain
    {
    private:
        int _width;
        int _height;
        Tile *_tiles;

    public:
        int width() { return _width; }

        int height() { return _height; }

        Tile &tile(int x, int y) { return _tiles[y * _width + x]; }

        Terrain(int width, int height)
            : _width(width), _height(height)
        {
            _tiles = new Tile[width * height];
        }

        ~Terrain()
        {
            delete[] _tiles;
        }
    };
} // namespace world
