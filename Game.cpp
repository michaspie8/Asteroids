//
// Created by Michal on 27.12.2023.
//

#include "Game.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "TextureManager.h"
#include "Colors.h"
#include "Mathf.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "Components/Renderer.h"
#include "Components/Asteroid.h"
#include <memory>

// gl window
#include <GLFW/glfw3.h>

Game *Game::s_pInstance = nullptr;

Game *Game::getInstance() {
    if (s_pInstance == nullptr) {
        s_pInstance = new Game();
        return s_pInstance;
    }
    return s_pInstance;
}

Game::Game() {
    m_Running = false;
    m_WindowWidth = 0;
    m_WindowHeight = 0;
    m_pWindow = nullptr;
    m_pRenderer = nullptr;
    m_DeltaTime = 0;
    m_AntiAliasingType = SSAA;
}

Game::~Game() = default;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        //init window
        /*auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(window);
        m_pWindow = SDL_CreateWindowFrom(window);*/

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        //init gl context
        //SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);
        //SDL_GL_CreateContext(m_pWindow);
        if (m_pWindow != nullptr) {
            //init renderer
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != nullptr) {
                //if everything is ok, set draw color to black and set window width and height
                SDL_Color b = colorFromHEX(ASTEROID_BLACK);
                SDL_SetRenderDrawColor(m_pRenderer, b.r, b.g, b.b, b.a);
                m_WindowWidth = width;
                m_WindowHeight = height;
                m_Running = true;

                //load textures
                TextureManager::getInstance()->load("assets/background-new.svg", "background_gradient");
                TextureManager::getInstance()->loadVector("assets/asteroid-1.svg", "asteroid-1");
                TextureManager::getInstance()->loadVector("assets/asteroid-2.svg", "asteroid-2");
                TextureManager::getInstance()->loadVector("assets/asteroid-3.svg", "asteroid-3");


                m_Colliders = std::vector<Collider *>();
                //init game objects
                m_GameObjects.push_back(new Player());
                m_GameObjects.push_back(Asteroid::MakeNew(3, {400, 200} ));
                m_GameObjects.push_back(Asteroid::MakeNew(3, {100, 500}));
                m_GameObjects.push_back(Asteroid::MakeNew(3, {800, 0}));

                //load textures for every obj in texture manager
                for (auto &gameObject: m_GameObjects) {
                    //if gameobject contains renderer component
                    Renderer *renderer = (Renderer *) gameObject->getComponent("Renderer");
                    if (renderer == nullptr) continue;
                    if (renderer->getRenderType() == RenderType::VECTOR) {
                        TextureManager::getInstance()->load("assets/" + renderer->getTextureId() + ".svg",
                                                            renderer->getTextureId());
                    } else if (renderer->getRenderType() == RenderType::SPRITE) {
                        TextureManager::getInstance()->loadVector("assets/" + renderer->getTextureId() + ".svg",
                                                                  renderer->getTextureId());

                    }
                }

                //add anti aliasing
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, m_AntiAliasingType == SSAA ? "best" : "0");


            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

void Game::handleEvents() {
    EventHandler::getInstance()->update();
}


void Game::update() {
    for (int i = 0; i < m_GameObjects.size(); i++) {
        if (m_GameObjects[i] != nullptr) m_GameObjects[i]->update();
    }


    //delete game objects marked for deletion
    for (int i = 0; i < m_GameObjects.size(); i++) {
        auto gameObject = m_GameObjects[i];
        if (gameObject->isMarkedForDeletion()) {
            delete gameObject;
            m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), gameObject),
                                m_GameObjects.end());
        }
    }
}

void Game::render() {
    //clear renderer
    SDL_RenderClear(m_pRenderer);
    //draw background gradient
    TextureManager::getInstance()->draw(TextureManager::getInstance()->getTexture("background_gradient"), 0, 0,
                                        m_WindowWidth, m_WindowHeight);

    //draw game objects
    for (auto &gameObject: m_GameObjects) {
        gameObject->draw();
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::addGameObject(GameObject *gameObject) {
    m_GameObjects.push_back(gameObject);
}

void Game::addCollider(Collider *collider) {
    m_Colliders.push_back(collider);
}

void Game::removeCollider(Collider *collider) {
    m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), collider), m_Colliders.end());
}

GameObject *Game::findGameObjectByName(const std::string& name) {
    for (auto &gameObject: m_GameObjects) {
        if (gameObject->getName() == name) {
            return gameObject;
        }
    }
    return nullptr;
}


std::vector<GameObject *> Game::findGameObjectsByName(const std::string& name) {
    std::vector<GameObject *> gameObjects;
    for (auto &gameObject: m_GameObjects) {
        if (gameObject->getName() == name) {
            gameObjects.push_back(gameObject);
        }
    }
    return gameObjects;
}

GameObject *Game::findGameObjectByTag(const std::string& tag) {
    for (auto &gameObject: m_GameObjects) {
        if (gameObject->getTag() == tag) {
            return gameObject;
        }
    }
    return nullptr;
}

std::vector<GameObject *> Game::findGameObjectsByTag(const std::string& tag) {
    std::vector<GameObject *> gameObjects;
    for (auto &gameObject: m_GameObjects) {
        if (gameObject->getTag() == tag) {
            gameObjects.push_back(gameObject);
        }
    }
    return gameObjects;
}


//bloom effect using gaussian blur and additive blending
void Game::bloom(Uint32 *pixels, int w, int h, int x, int y, float opacity, int blurRadius, float blurSensitivity) {
    //if(w*4>getWindowWidth())
    w = getWindowWidth();
    //if(h*4>getWindowHeight())
    h = getWindowHeight();
    //blur the pixels
    pixels = Mathf::GaussianBlur(pixels, m_WindowWidth, m_WindowHeight, 5, 1);

    //fill texture with pixels
    auto bloomTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_UpdateTexture(bloomTexture, NULL, pixels, m_WindowWidth * sizeof(Uint32));

    //set blend mode to additive
    SDL_SetTextureBlendMode(bloomTexture, SDL_BLENDMODE_ADD);

    SDL_RenderCopy(m_pRenderer, bloomTexture, NULL, NULL);

    //free memory
    delete[] pixels;
    SDL_DestroyTexture(bloomTexture);
}


