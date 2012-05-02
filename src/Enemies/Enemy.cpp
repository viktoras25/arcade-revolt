#include "Enemy.h"

Enemy::Enemy(){}
void Enemy::Die() {}

void Enemy::Loop() {
    Entity::Loop();

    if (rand()%MAX_FPS*1 == 1) {
        // Change direction
//        std::cout << "Changing speed from: " << SpeedX << "  " << SpeedY << std::endl;
        float speed = abs( abs(SpeedX) > abs(SpeedY) ? SpeedX : SpeedY );
//        std::cout << "Speed: " << speed << std::endl;
        switch (rand()%3) {
            case 0:
                SpeedX = -speed;
                SpeedY = 0;
            break;
            case 1:
                SpeedY = -speed;
                SpeedX = 0;
            break;
            case 2:
                SpeedX = speed;
                SpeedY = 0;
            break;
            case 3:
                SpeedX = 0;
                SpeedY = speed;
            break;
        }
//        std::cout << "Changing speed to: " << SpeedX << "  " << SpeedY << std::endl << std::endl;
    }

    if (SpeedX > 0 || SpeedY > 0) AnimState = 0;
    if (SpeedX < 0 || SpeedY < 0) AnimState = 1;
}

bool Enemy::Init() {
    return Entity::Load(File, BLOCK_SIZE, BLOCK_SIZE, 2);
}

bool Enemy::Load(const char* File, int Width, int Height, int MaxFrames) {
    return Entity::Load(File, Width, Height, MaxFrames);
}

bool Enemy::Collision(Entity* E) {
    // Entity-to-map collision
    if (E == NULL) {
        int dice = rand()%100;
        if (abs(SpeedX) > 0) {

            //50% to go in opposite direction
            if (dice > 50 && CanMove(X - SpeedX, Y)) {
//                std::cout << "Diced " << dice << " to go in the opposite direction. Speed " << SpeedX;
                SpeedX = -SpeedX;
//                std::cout << " to " << SpeedX << std::endl;
            } else if (dice > 25 && CanMove(X, Y + SpeedX)) {
//                std::cout << "Diced " << dice << " to go down. Speed " << SpeedX << " " << SpeedY;
                if (SpeedY == 0) SpeedY = SpeedX;
                SpeedX = 0;
//                std::cout << " to " << SpeedX << " " << SpeedY << std::endl;
            } else {
//                std::cout << "Diced " << dice << " to go up. Speed " << SpeedX << " " << SpeedY;
                if (SpeedY == 0) SpeedY = -SpeedX;
                SpeedX = 0;
//                std::cout << " to " << SpeedX << " " << SpeedY << std::endl;
            }
        }

        if (abs(SpeedY) > 0) {

            //50% to go in opposite direction
            if (dice > 50) {
//                std::cout << "Diced " << dice << " to go in the opposite direction. Speed " << SpeedY;
                SpeedY = -SpeedY;
//                std::cout << " to " << SpeedY << std::endl;
            } else if (dice > 25) {
//                std::cout << "Diced " << dice << " to go right direction. Speed " << SpeedY << " " << SpeedX;
                if (SpeedX == 0) SpeedX = SpeedY;
                SpeedY = 0;
//                std::cout << " to " << SpeedX << " " << SpeedY << std::endl;
            } else {
                if (SpeedX == 0) SpeedX = -SpeedY;
                SpeedY = 0;
            }
        }

        return false;
    } else {
        ;
    }

    return true;
}

void Enemy::Kill() {
    Entity* E = Entity::EntityList.back();
    ((Enemy *)E)->Die();
}
