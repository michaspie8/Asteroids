//
// Created by Michal on 02.01.2024.
//

#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "Component.h"
#include "LoaderParams.h"
#include "Vector.h"
#include "GameObject.h"
#include "SDL.h"


class Bullet : public Component {

public:
    Bullet(int speed, int damage, std::string name = "Bullet") : Component(name) {
        m_Speed = speed;
        m_Damage = damage;
        lifeTimer = SDL_GetTicks();
    };

    ~Bullet() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void OnCollisionEnter(GameObject *other);

    void setSpeed(int speed);

    void setDamage(int damage);

    int getSpeed();

    int getDamage();

protected:
    int m_Speed;
    float lifeTime = 0;
    int m_Damage;
    unsigned int lifeTimer;

};


#endif //ASTEROIDS_BULLET_H
