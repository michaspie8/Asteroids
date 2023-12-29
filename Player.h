//
// Created by Michal on 27.12.2023.
//

#include "GameObject.h"

#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H


class Player : public GameObject {
public:
    Player(const LoaderParams *params, float angleDampTime, float rotationSpeed);

    Player();

    ~Player() override;

    void draw() override;

    void update() override;

    void clean() override;


protected:
    float angleDampVelocity = 0;
    float angleDampTime = 0.1f;
    float rotationSpeed = 1;
    GameObject *m_pBullet;
    float bulletSpeed = 10;
    float bulletLifeTime = 1;
    float bulletSpawnTime = 0;
    float bulletSpawnDelay = 0.1f;

    GameObject *m_JetFlame;
};


#endif //ASTEROIDS_PLAYER_H
