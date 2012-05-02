#include "Valcom.h"

Valcom::Valcom() {
    Speed = 1;
    File = "./gfx/valcom.png";
    Points = 100;

    int direction = rand()%3;
    switch (direction) {
        case 0: SpeedX = -Speed; break;
        case 1: SpeedY = -Speed; break;
        case 2: SpeedX = Speed;  break;
        case 3: SpeedY = Speed;  break;
    }
}

bool Valcom::Create() {

    float X, Y;

    Map::Instance.GetFreeSpace(&X, &Y);

    Valcom* V = new Valcom();
    if (V->Init() == false) return false;
    V->Place(X*BLOCK_SIZE, Y*BLOCK_SIZE);
    Entity::EntityList.push_back(V);

    return true;
}

void Valcom::Die() {
    //DeadTimer = SDL_GetTicks();
    Anim.MaxFrames = 1;
    Anim.SetCurrentFrame(0);
    AnimState = 2;
    SpeedX = 0;
    SpeedY = 0;
    Dead = true;

    //Animation DeathAnimation = new Animation();
    //Animation::AnimationList.push_back();
}
