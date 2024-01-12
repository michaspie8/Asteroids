//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "../GameObject.h"
#include "Component.h"

class Asteroid : public Component {

public:
    Asteroid(int size);

    void draw() override;

    void update() override;

    void clean() override { Component::clean(); };

    static GameObject *MakeNew(int size, Vector2 pos,float angle = 0, float speed = 1 );

    //Destorys asteroid and creates 2-5 smaller ones, if asteroid is small, it just destroys it
    void Destroy(Vector2 contactPoint , float speed);

    void setSize(int size);

    int getSize() const;


protected:
    //Asteroids appear in 3 sizes
    int m_Size;


};


#endif //ASTEROIDS_ASTEROID_H
