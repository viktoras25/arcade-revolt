#ifndef VALCOM_H
#define VALCOM_H

#include <Entity.h>
#include <Enemy.h>
#include <Define.h>
#include <iostream>

class Valcom : public Enemy {
    public:
        Valcom();
        virtual bool Init();
        virtual void Loop();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Collision(Entity* E);
        virtual void Cleanup();
        static bool Create();
        virtual void Die();
};

#endif // VALCOM_H
