#include "Animation.h"

std::vector<Animation*> Animation::AnimationList;

Animation::Animation() {
    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;
    AnimState       = 0;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
    Dispose         = false;

    Surface = NULL;
}

Animation::Animation(const char* File, unsigned int W, unsigned int H, int FrameRate) {

    Surface = NULL;

    Surface = Sprite::Load(File);

    Sprite::Transparent(Surface, 255, 0, 255);

    Width = W;
    Height = H;

    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;
    AnimState       = 0;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
    Dispose         = false;
}

void Animation::Animate() {
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    OldTime = SDL_GetTicks();

    CurrentFrame += FrameInc;

    if (Once && CurrentFrame > MaxFrames) {
        Dispose = true;
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

Animation::~Animation() {
    SDL_FreeSurface(Surface);
}

void Animation::Render(SDL_Surface* Screen, int X, int Y) {
    if (Surface == NULL || Screen == NULL) return;
    Sprite::Draw(Screen, Surface, X, Y, CurrentFrame*Width, AnimState*Height, Width, Height);
}
