#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>
#include <Define.h>
#include <iostream>

class Enemy : public Entity {
    protected:
        bool Dead;
        int Points;
        Uint32 DeadTimer;
    public:
        Enemy();
        virtual void Loop();
        //virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Init();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual bool Collision(Entity* E);
        virtual void Die();
        static void Kill();
};

#endif // ENEMY_H
