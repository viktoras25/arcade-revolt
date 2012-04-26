#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
    public:
        Sprite();
        static SDL_Surface* Load(const char* File);
        static bool Draw(SDL_Surface* Canvas, SDL_Surface* Sprite, int X, int Y);
        static bool Draw(SDL_Surface* Canvas, SDL_Surface* Sprite, int X, int Y, int X2, int Y2, int W, int H);
        static bool Transparent(SDL_Surface* Surface, int R, int G, int B);
};

#endif // SPRITE_H
