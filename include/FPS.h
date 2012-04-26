#ifndef FPS_H
#define FPS_H

#include <SDL.h>
#include <Define.h>

class FPS
{
    public:
        static FPS Instance;

    private:
        unsigned int Tick;
        int LastTime;

        float SpeedFactor;

        int NumFrames;
        int Frames;

    public:
        FPS();
        void Loop();
        int GetFPS();
        float GetSpeedFactor();
};

#endif // FPS_H
