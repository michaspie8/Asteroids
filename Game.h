//
// Created by Michal on 27.12.2023.
//

#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SDL.h>
#include "GameObject.h"
#include <vector>
#include "Components/Collider.h"

enum AntiAliasingType {
    MSAA,
    FXAA,
    SSAA
};

class Game {
public:

    bool init(const char *title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags);

    static void handleEvents();

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
    [[nodiscard]] unsigned int getDeltaTime() const { return m_DeltaTime; }

    [[nodiscard]] bool isRunning() const { return m_Running; }

    [[nodiscard]] SDL_Renderer *getRenderer() const { return m_pRenderer; }

    [[nodiscard]] SDL_Window *getWindow() const { return m_pWindow; }

    [[nodiscard]] int getWindowWidth() const { return m_WindowWidth; }

    [[nodiscard]] int getWindowHeight() const { return m_WindowHeight; }

    [[nodiscard]] GameObject *findGameObjectByName(const std::string& name);

    [[nodiscard]] std::vector<GameObject *> findGameObjectsByName(const std::string& name);

    [[nodiscard]] GameObject *findGameObjectByTag(const std::string& tag);

    [[nodiscard]] std::vector<GameObject *> findGameObjectsByTag(const std::string& tag);

    [[nodiscard]] std::vector<GameObject *> getGameObjects() const { return m_GameObjects; }

    [[nodiscard]] AntiAliasingType getAntiAliasingType() const { return m_AntiAliasingType; }

    [[nodiscard]] std::vector<Collider *> getColliders() const { return m_Colliders; }

    static Game *getInstance();


    void bloom(Uint32 *pixels, int w, int h, int x, int y, float opacity, int blurRadius, float blurSensitivity);

private:
    Game();

    ~Game();

    static Game *s_pInstance; //singleton
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    bool m_Running;
    int m_WindowWidth;
    int m_WindowHeight;
    unsigned int m_DeltaTime;
    AntiAliasingType m_AntiAliasingType;

    std::vector<GameObject *> m_GameObjects;
    std::vector<Collider *> m_Colliders;
};

#endif //ASTEROIDS_GAME_H
