#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>
#include "Sprite.h"

class Animation {
    private:
    public:
        int CurrentFrame;
        int FrameInc;
        int FrameRate;
        Uint32 OldTime;
        SDL_Surface* Surface;
        unsigned int Width;
        unsigned int Height;

    public:
        static std::vector<Animation*> AnimationList;

        int MaxFrames;
        int AnimState;
        bool Oscillate;
        bool Once;
        bool Dispose;

    public:
        Animation();
        Animation(const char* File, unsigned int W, unsigned int H, int FrameRate);
        ~Animation();
        void Animate();

        void Render(SDL_Surface* Surface, int vX, int vY);

        void SetFrameRate(int Rate);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();
};

#endif // ANIMATION_H
