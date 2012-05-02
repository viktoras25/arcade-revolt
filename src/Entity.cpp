#include "Entity.h"

std::vector<Entity*> Entity::EntityList;
std::vector<EntityCollision*> EntityCollision::CollisionList;

EntityCollision::EntityCollision() {
    A = NULL;
    B = NULL;
}

EntityCollision::EntityCollision(Entity* A, Entity* B) {
    this->A = A;
    this->B = B;
}

Entity::Entity() {
    Surface = NULL;
    X = Y = 0.0f;
    AnimState = 0;

    Flags = 0;

    SpeedX = 0.0;
    SpeedY = 0.0;
}

Entity::~Entity() {}

bool Entity::Init() {
    return true;
}

bool Entity::Load(const char* File, int Width, int Height, int MaxFrames) {

    if ((Surface = Sprite::Load(File)) == NULL) {
        std::cerr << "File " << File << " not found" << std::endl;
        return false;
    }

    Sprite::Transparent(Surface, 255, 0, 255);

    this->Width = Width;
    this->Height = Height;

    Anim.MaxFrames = MaxFrames;
    Anim.Oscillate = true;
    Anim.SetFrameRate(200);

    return true;
}

void Entity::Loop() {
    Move(SpeedX, SpeedY);
    Anim.Animate();
}

void Entity::Render(SDL_Surface* Screen, int vX, int vY) {
    if (Surface == NULL || Screen == NULL) return;
    Sprite::Draw(Screen, Surface, vX+X, vY+Y, Anim.GetCurrentFrame() * Width, AnimState*Height, Width, Height);
}

void Entity::Cleanup() {
    SDL_FreeSurface(Surface);
    Surface = NULL;
}

bool Entity::Collision(Entity* E) {
    return true;
}

/**
 * Moves entity by X and Y pixels, checks collisions
 * @var float MoveX
 * @var float MoveY
 */
void Entity::Move(float MoveX, float MoveY) {
    if (MoveX == 0 && MoveY == 0) return;

    float StepX = 0;
    float StepY = 0;
    //float SF = FPS::Instance.GetSpeedFactor();
    float SF = 1;

    //MoveX *= SF;
    //MoveY *= SF;

    // We approach by SF at a time
    if (MoveX > 0) {
        if (MoveX > 1) {
            StepX = 1;
        } else {
            StepX = MoveX;
        }
    } else if (MoveX < 0) {
        if (MoveX < -1) {
            StepX = -1;
        } else {
            StepX = MoveX;
        }
    }

    if (MoveY > 0) {
        if (MoveY > 1) {
            StepY = 1;
        } else {
            StepY = MoveY;
        }
    } else if (MoveY < 0) {
        if (MoveY < -1) {
            StepY = -1;
        } else {
            StepY = MoveY;
        }
    }

    while (true) {
//        if (Flags & ENTITY_FLAG_GHOST) {
//            CanMove((int)(X + StepX), (int)(Y + StepY));
//            X += StepX;
//            Y += StepY;
//        } else {
            if (CanMove((int)(X + StepX), (int)Y)) {
                X += StepX;
            } else {
                //SpeedX = 0;
                // Handle collision
                Collision(NULL);
                MoveX = 0;
            }

            if (CanMove((int)X, (int)(Y + StepY))) {
                Y += StepY;
            } else {
                // Handle collision
                Collision(NULL);
                MoveY = 0;
                //SpeedY = 0;
            }
//        }
//            if (CanMove(X+StepX, Y+StepY)) {
//                Y += StepY;
//                X += StepX;
//            } else {
//                MoveY = 0;
//                MoveX = 0;
//            }

        MoveX += -StepX;
        MoveY += -StepY;

        if(StepX > 0 && MoveX <= 0) StepX = 0;
        if(StepX < 0 && MoveX >= 0) StepX = 0;

        if(StepY > 0 && MoveY <= 0) StepY = 0;
        if(StepY < 0 && MoveY >= 0) StepY = 0;

        if(MoveX == 0) StepX = 0;
        if(MoveY == 0) StepY = 0;

        if(MoveX == 0 && MoveY == 0) break;
        if(StepX  == 0 && StepY == 0) break;
    }
}

bool Entity::CanMove(int NewX, int NewY) {

    int top = (int)NewX/BLOCK_SIZE;
    int left = (int)NewY/BLOCK_SIZE;

    for (int i=top; i < top+2; i++) {
        for (int j = left; j < left+2; j++) {
            if (Map::Instance.Tiles[i][j] == NULL) continue;
            if (Flags & ENTITY_FLAG_GHOST && Map::Instance.Tiles[i][j]->Type == TILE_TYPE_BRICK) continue;
            if (Collides(NewX, NewY, i*BLOCK_SIZE, j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)) {
                //EntityCollision::CollisionList.push_back(new EntityCollision(this, NULL));
                return false;
            }
        }
    }

    return true;
}

bool Entity::Collides(int X, int Y, int cX, int cY, int cW, int cH) {
    int Left1 = (int)X, Top1 = (int)Y;
    int Right1 = (int)X + BLOCK_SIZE - 1, Bottom1 = (int)Y + BLOCK_SIZE - 1;

    int Left2 = cX, Top2 = cY;
    int Right2 = cX + cW, Bottom2 = cY + cH;

    if (Bottom1 < Top2) return false;
    if (Top1 > Bottom2) return false;
    if (Right1 < Left2) return false;
    if (Left1 > Right2) return false;

    return true;
}

void Entity::Place(float X, float Y) {
    this->X = X;
    this->Y = Y;
}
