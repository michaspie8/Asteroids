//
// Created by Michal on 27.12.2023.
//

#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SDL.h>
#include "GameObject.h"
#include <vector>
enum AntiAliasingType {
    MSAA,
    FXAA,
    SSAA
};
class Game {
public:

    bool init(const char *title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags);

    void handleEvents();

    void update();

    void render();

    void clean();

    //setters
    void setRunning(bool running) { m_Running = running; }

    void setDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }

    //getters
    [[nodiscard]] float getDeltaTime() const { return m_DeltaTime; }

    [[nodiscard]] bool isRunning() const { return m_Running; }

    [[nodiscard]] SDL_Renderer *getRenderer() const { return m_pRenderer; }

    [[nodiscard]] SDL_Window *getWindow() const { return m_pWindow; }

    [[nodiscard]] int getWindowWidth() const { return m_WindowWidth; }

    [[nodiscard]] int getWindowHeight() const { return m_WindowHeight; }

    static Game *getInstance();


private:
    Game();

    ~Game();

    void antiAliasing(int samples, AntiAliasingType type );

    static Game *s_pInstance; //singleton
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    bool m_Running;
    int m_WindowWidth;
    int m_WindowHeight;
    float m_DeltaTime;
    AntiAliasingType m_AntiAliasingType;

    std::vector<GameObject *> m_GameObjects;
};

#endif //ASTEROIDS_GAME_H
