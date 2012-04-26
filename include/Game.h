#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Sprite.h"
#include "Event.h"
#include "Animation.h"
#include "Entity.h"
#include "FPS.h"
#include "Define.h"
#include "Map.h"

#include "Valcom.h"
#include "Oneal.h"
#include "Dahl.h"
#include "Minvo.h"
#include "Ovape.h"
#include "Doria.h"
#include "Pass.h"
#include "Pontan.h"

#include <iostream>
#include <time.h>

class Game : public Event {
    private:
        bool Running;
        SDL_Surface* Screen;

    public:
        Game();
        int Execute();

        bool Init();
        void Loop();
        void HandleEvent(SDL_Event* Event);
        void Render();
        void Cleanup();

        void Exit();
};

#endif // GAME_H
