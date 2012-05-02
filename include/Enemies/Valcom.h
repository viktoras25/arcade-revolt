#ifndef VALCOM_H
#define VALCOM_H

#include <Entity.h>
#include <Enemy.h>
#include <Define.h>
#include <iostream>

class Valcom : public Enemy {
    public:
        Valcom();
        static bool Create();
        virtual void Die();
};

#endif // VALCOM_H
