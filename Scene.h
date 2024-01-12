//
// Created by Michal on 09.01.2024.
//

#ifndef ASTEROIDS_SCENE_H
#define ASTEROIDS_SCENE_H


class Scene {

public:
    Scene() = default;

    ~Scene() = default;

    void draw();

    void update();

    void clean();

    void handleEvents();




};


#endif //ASTEROIDS_SCENE_H
