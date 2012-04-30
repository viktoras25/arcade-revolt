#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>

class Animation {
    private:
        int CurrentFrame;
        int FrameInc;

        int FrameRate;
        unsigned long OldTime;

    public:
        static std::vector<Animation*> AnimationList;

        int MaxFrames;
        bool Oscillate;
        bool Once;

    public:
        Animation();
        ~Animation();
        void Animate();

        void SetFrameRate(int Rate);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();
};

#endif // ANIMATION_H
