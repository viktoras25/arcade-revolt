#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>
#include <Define.h>
#include <Tile.h>
#include <Sprite.h>

#include <iostream>

class Map {

    public:
        std::vector< std::vector<Tile*> > Tiles;

    public:
        SDL_Surface* Surface;
        static Map Instance;

    public:
        void Init();
        bool Load(const char* Filename);
        void Render(SDL_Surface* Screen, int OffsetX, int OffsetY);
        void Cleanup();
        void GetFreeSpace(float* X, float* Y);

    private:
        Map();
};

#endif // MAP_H
