//
// Created by Michal on 02.01.2024.
//

#ifndef ASTEROIDS_SCENEMANAGER_H
#define ASTEROIDS_SCENEMANAGER_H

#include <vector>
#include "Game.h"


class SceneManager {

public:
    SceneManager() = default;

    ~SceneManager() = default;

    void addScene(Game *scene);

    void changeScene(int sceneNumber);

    void update();

    void draw();

    void clean();

};


#endif //ASTEROIDS_SCENEMANAGER_H
