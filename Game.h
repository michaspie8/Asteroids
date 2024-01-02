//
// Created by Michal on 27.12.2023.
//

#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SDL.h>
#include "GameObject.h"
#include <vector>
#include "Collider.h"

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

    void addGameObject(GameObject *gameObject);

    void addCollider(Collider *collider);

    void removeCollider(Collider *collider);

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

    [[nodiscard]] GameObject *findGameObjectByName(std::string name);

    [[nodiscard]] std::vector<GameObject *> findGameObjectsByName(std::string name);

    [[nodiscard]] GameObject *findGameObjectByTag(std::string tag);

    [[nodiscard]] std::vector<GameObject *> findGameObjectsByTag(std::string tag);

    [[nodiscard]] std::vector<GameObject *> getGameObjects() const { return m_GameObjects; }

    [[nodiscard]] AntiAliasingType getAntiAliasingType() const { return m_AntiAliasingType; }

    [[nodiscard]] std::vector<Collider *> getColliders() const { return m_Colliders; }

    static Game *getInstance();


private:
    Game();

    ~Game();

    //void bloom(float opacity, int blurRadius, float blurSensitivity);

    static Game *s_pInstance; //singleton
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    bool m_Running;
    int m_WindowWidth;
    int m_WindowHeight;
    float m_DeltaTime;
    AntiAliasingType m_AntiAliasingType;

    std::vector<GameObject *> m_GameObjects;
    std::vector<Collider *> m_Colliders;
};

#endif //ASTEROIDS_GAME_H
