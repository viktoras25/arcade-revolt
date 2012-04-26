#include <SDL.h>
#include "Sprite.h"

Sprite::Sprite() { }

SDL_Surface* Sprite::Load(const char* File) {
    SDL_Surface* tmp = NULL;
    SDL_Surface* result = NULL;

    if ((tmp = IMG_Load(File)) == NULL) {
        return NULL;
    }

    if (tmp->format->Amask) {
        result = SDL_DisplayFormatAlpha(tmp);
    } else {
        result = SDL_DisplayFormat(tmp);
    }
    SDL_FreeSurface(tmp);

    return result;
}

bool Sprite::Draw(SDL_Surface* Canvas, SDL_Surface* Sprite, int X, int Y) {
    if (Canvas == NULL || Sprite == NULL) {
        return false;
    }

    SDL_Rect Area;
    Area.x = X;
    Area.y = Y;

    SDL_BlitSurface(Sprite, NULL, Canvas, &Area);

    return true;
}

bool Sprite::Draw(SDL_Surface* Canvas, SDL_Surface* Sprite, int X, int Y, int X2, int Y2, int W, int H) {
    if (Canvas == NULL || Sprite == NULL) {
        return false;
    }

    SDL_Rect DstArea;
    DstArea.x = X;
    DstArea.y = Y;
    SDL_Rect SrcArea = {X2, Y2, W, H};

    SDL_BlitSurface(Sprite, &SrcArea, Canvas, &DstArea);

    return true;
}

bool Sprite::Transparent(SDL_Surface* Surface, int R, int G, int B) {
    if (Surface == NULL) {
        return false;
    }

    SDL_SetColorKey(Surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surface->format, R, G, B));
    return true;
}
