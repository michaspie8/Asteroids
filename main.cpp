#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>


const int TARGET_FPS = 60;
const int TARGET_FRAMETIME = 1000 / TARGET_FPS;
int frameStart, frameTime;

int main(int argc, char *argv[]) {

    srand(time(nullptr));

    if (Game::getInstance()->init("Asteroid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800,
                                  SDL_WINDOW_SHOWN)) {
        while (Game::getInstance()->isRunning()) {
            frameStart = SDL_GetTicks64();
            Game::getInstance()->handleEvents();
            Game::getInstance()->update();
            Game::getInstance()->render();
            frameTime = SDL_GetTicks64() - frameStart;

            if (frameTime < TARGET_FRAMETIME) {
                SDL_Delay(TARGET_FRAMETIME - frameTime);

            }
            //delta time will measure how much time has passed since last frame
            Game::getInstance()->setDeltaTime((float) SDL_GetTicks64() - frameStart / 1000);


        }
        Game::getInstance()->clean();
    }
    return 0;
}

