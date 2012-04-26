#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>

class Animation {
    private:
        int CurrentFrame;
        int FrameInc;

        int FrameRate;
        unsigned long OldTime;

    public:
        int MaxFrames;
        bool Oscillate;

    public:
        Animation();
        void Animate();

        void SetFrameRate(int Rate);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();
};

#endif // ANIMATION_H
