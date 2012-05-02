#include "Animation.h"

std::vector<Animation*> Animation::AnimationList;

Animation::Animation() {
    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
    Finished        = false;
}

void Animation::Animate() {
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    OldTime = SDL_GetTicks();

    CurrentFrame += FrameInc;

    if (Once && CurrentFrame > MaxFrames) {
        Finished = true;
        return;
    }

    if(Oscillate && CurrentFrame >= MaxFrames) {
        CurrentFrame = 0;
    } else if(CurrentFrame >= MaxFrames || CurrentFrame <= 0) {
        FrameInc = -FrameInc;
    }
}

void Animation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}

void Animation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}

int Animation::GetCurrentFrame() {
    return CurrentFrame;
}

Animation::~Animation() {}
