//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "GameObject.h"

class Asteroid : public Component {

public:
    Asteroid(Vector2 pos) : Component("Asteroid"){};

    void draw() override;

    void update() override;

    void clean() override;

    //Destorys asteroid and creates 2-5 smaller ones, if asteroid is small, it just destroys it
    void Destroy();
protected:

    float m_Speed;
    //Asteroids appear in 3 sizes
    int m_Size;


};


#endif //ASTEROIDS_ASTEROID_H
