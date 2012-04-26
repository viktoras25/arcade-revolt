#ifndef PONTAN_H
#define PONTAN_H

#include <Entity.h>
#include <Define.h>
#include <iostream>

class Pontan : public Entity {
    private:
        int Points;
    public:
        Pontan();
        virtual bool Init();
        virtual void Loop();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Collision(Entity* E);
        virtual void Cleanup();
        static bool Create();
};

#endif // PONTAN_H
