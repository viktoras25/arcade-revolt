#include "FPS.h"

FPS FPS::Instance;

FPS::FPS() {
    Tick = 0;
    SpeedFactor = 0;
    Frames = 0;
    NumFrames = 0;
}

void FPS::Loop() {
    if (Tick + 1000 < SDL_GetTicks()) {
        Tick = SDL_GetTicks();

        NumFrames = Frames;
        Frames = 0;
    }

    SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * DEFAULT_FPS;
    LastTime = SDL_GetTicks();

    Frames++;

    int delay = 1000/MAX_FPS-SDL_GetTicks() + LastTime;
    if (delay > 0) SDL_Delay(delay);
}

int FPS::GetFPS() {
    return NumFrames;
}

float FPS::GetSpeedFactor() {
    return SpeedFactor;
}
