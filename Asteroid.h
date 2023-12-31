/*
//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {

public:
    Asteroid(const LoaderParams *params) : GameObject(params) {};

    ~Asteroid() : ~GameObject() {};

    void draw() override;

    void update() override;

    void clean() override;

};


#endif //ASTEROIDS_ASTEROID_H
*/
