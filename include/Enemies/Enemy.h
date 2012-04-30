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
        virtual void Die();
        static void Kill();
};

#endif // ENEMY_H
