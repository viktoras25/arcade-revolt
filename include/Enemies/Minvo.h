#ifndef MINVO_H
#define MINVO_H

#include <Entity.h>
#include <Define.h>

class Minvo : public Entity {
    private:
        int Points;
    public:
        Minvo();
        virtual bool Init();
        virtual void Loop();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Collision(Entity* E);
        virtual void Cleanup();
        static bool Create();
};

#endif // MINVO_H
