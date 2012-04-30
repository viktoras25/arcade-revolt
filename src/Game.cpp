#include "Game.h"

Game::Game() {
    Screen = NULL;
    Running = true;
}

int Game::Execute() {
    if (Init() == false) {
        return -1;
    }

    SDL_Event Event;

    while (Running) {
        while(SDL_PollEvent(&Event)) {
            HandleEvent(&Event);
        }

        Loop();
        Render();
    }

    Cleanup();

    return 0;
}

bool Game::Init() {

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((Screen = SDL_SetVideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    Map::Instance.Init();
    Map::Instance.Load("./gfx/sprites.png");



    for (int i = 0; i < 100; i++) {
        Valcom::Create();
    }
//    Oneal::Create();
//    Dahl::Create();
//    Minvo::Create();
//    Ovape::Create();
//    Doria::Create();
//    Pass::Create();
//    Pontan::Create();

    ViewX = 0;
    ViewY = 0;
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    return true;
}

void Game::Loop() {

    // Handle simple animations
    for (unsigned int i = 0; i < Animation::AnimationList.size(); i++) {
        if (!Animation::AnimationList[i]) continue;
        Animation::AnimationList[i]->Animate();
    }

    // Handle entities
    for (unsigned int i = 0; i < Entity::EntityList.size(); i++) {
        if (!Entity::EntityList[i]) continue;
        Entity::EntityList[i]->Loop();
    }

    for (unsigned int i = 0; i < EntityCollision::CollisionList.size(); i++) {
        Entity* A = EntityCollision::CollisionList[i]->A;
        Entity* B = EntityCollision::CollisionList[i]->B;

        if (A == NULL) continue;

        // Entity-map collision
        if (B == NULL) {
            A->Collision(B);
        } else {
            if (A->Collision(B)) {
                B->Collision(A);
            }
        }
    }
    EntityCollision::CollisionList.clear();

    FPS::Instance.Loop();

    char Buffer[255];
    sprintf(Buffer, "FPS: %d, SpeedRatio: %f", FPS::Instance.GetFPS(), FPS::Instance.GetSpeedFactor());
    SDL_WM_SetCaption(Buffer, Buffer);

    return;
}

void Game::HandleEvent(SDL_Event* Event) {
    Event::Handle(Event);
    return;
}

void Game::Render() {

    SDL_FillRect(Screen, NULL, 0x000000);

    Map::Instance.Render(Screen, ViewX, ViewY);

    for (unsigned int i = 0; i < Entity::EntityList.size(); i++) {
        if (!Entity::EntityList[i]) continue;
        Entity::EntityList[i]->Render(Screen, ViewX, ViewY);
    }

    SDL_Flip(Screen);
    return;
}

void Game::Cleanup() {

    for (unsigned int i = 0; i < Entity::EntityList.size(); i++) {
        if (!Entity::EntityList[i]) continue;
        Entity::EntityList[i]->Cleanup();
    }
    Entity::EntityList.clear();

    SDL_FreeSurface(Screen);
    SDL_Quit();
    return;
}

void Game::Exit() {
    Running = false;
}
