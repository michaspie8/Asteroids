//
// Created by Michal on 27.12.2023.
//

#include "Game.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "TextureManager.h"
#include "Colors.h"

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
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
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

                //init game objects
                m_GameObjects.push_back(new Player());
                //add
                //load textures for every obj in texture manager
                for (auto &gameObject: m_GameObjects) {
                    TextureManager::getInstance()->load("assets/" + gameObject->getTextureId() + ".svg",
                                                        gameObject->getTextureId());
                }
                //load vector textures for every obj in texture manager
                for (auto &gameObject: m_GameObjects) {
                    TextureManager::getInstance()->loadVector("assets/" + gameObject->getTextureId() + ".svg",
                                                              gameObject->getTextureId());
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
    for (auto &gameObject: m_GameObjects) {
        gameObject->update();
    }
}

void Game::render() {
    //set color to asteroid black
    SDL_Color b = colorFromHEX(ASTEROID_BLACK);
    SDL_SetRenderDrawColor(m_pRenderer, b.r, b.g, b.b, b.a);
    //clear renderer
    SDL_RenderClear(m_pRenderer);
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