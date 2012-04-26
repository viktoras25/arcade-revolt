#ifndef DAHL_H
#define DAHL_H

#include <Entity.h>
#include <Define.h>

class Dahl : public Entity {
    private:
        int Points;
    public:
        Dahl();
        virtual bool Init();
        virtual void Loop();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Collision(Entity* E);
        virtual void Cleanup();
        static bool Create();
};

#endif // DAHL_H
