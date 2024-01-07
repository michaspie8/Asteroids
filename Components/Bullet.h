//
// Created by Michal on 02.01.2024.
//

#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "Component.h"
#include "../LoaderParams.h"
#include "../Vector.h"
#include "../GameObject.h"
#include "SDL.h"


class Bullet : public Component {

public:
    Bullet(float speed, int damage, int lifeTime = 700, std::string name = "Bullet") : Component(name) {
        m_Speed = speed;
        m_Damage = damage;
        m_LifeTime = lifeTime;
        m_LifeTimer = 0;
    };

    ~Bullet() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void OnCollisionEnter(GameObject *other);

    void setSpeed(float speed);

    void setDamage(int damage);

    float getSpeed();

    int getDamage();

protected:
    float m_Speed;
    unsigned int m_LifeTime = 0;
    int m_Damage;
    unsigned int m_LifeTimer;

};


#endif //ASTEROIDS_BULLET_H
