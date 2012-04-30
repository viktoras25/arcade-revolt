#include "Enemy.h"

Enemy::Enemy(){}
void Enemy::Die() {}

void Enemy::Kill{
    Entity* E = Entity::EntityList.back();
    E->Die();
}
