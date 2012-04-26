#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Animation.h"
#include "Sprite.h"
#include "FPS.h"
#include "Map.h"

#include <iostream>

enum {
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE = 0x00000000,
    ENTITY_FLAG_GRAVITY = 0x00000001,
    ENTITY_FLAG_GHOST = 0x00000002,
    ENTITY_FLAG_MAPONLY = 0x00000003
};

class Entity {
    protected:
        Animation Anim;
        SDL_Surface* Surface;

    protected:
        const char* File;

        float Speed;

        int Width;
        int Height;

    public:

        float SpeedX;
        float SpeedY;

        // Current coordinates
        float X;
        float Y;

        int AnimState;

        int Type;
        bool Dead;
        int Flags;

        static std::vector<Entity*> EntityList;

    public:
        Entity();
        virtual ~Entity();

        virtual bool Init();
        virtual bool Load(const char* File, int Width, int Height, int MaxFrames);
        virtual void Loop();
        virtual void Render(SDL_Surface* Surface, int vX, int vY);
        virtual bool Collision(Entity* E);
        virtual void Cleanup();

        void Move(float MoveX, float MoveY);
        void Stop();
        bool Collides(int NewX, int NewY, int cX, int cY, int cW, int cH);
        void Place(float X, float Y);

    protected:
        bool CanMove(int NewX, int NewY);
};

class EntityCollision {
    public:
        static std::vector<EntityCollision*> CollisionList;

    public:
        Entity* A;
        Entity* B;

    public:
        EntityCollision();
        EntityCollision(Entity* A, Entity* B);
};

#endif // ENTITY_H
