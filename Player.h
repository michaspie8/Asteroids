//
// Created by Michal on 27.12.2023.
//

#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    Player(const LoaderParams &params, float angleDampTime, float rotationSpeed);

    Player();

    ~Player() override;

    void draw() override;

    void update() override;

    void clean() override;

    void OnCollisionEnter(GameObject *other);


protected:
    float angleDampVelocity = 0;
    float angleDampTime = 0.1f;
    float rotationSpeed = 1;
    GameObject *m_pBullet;
    float m_bulletSpeed = 10;
    float m_bulletLifeTime = 1;
    float m_bulletSpawnTime = 0;
    float m_bulletSpawnDelay = 0.1f;

    GameObject *m_JetFlame;
    unsigned int m_jetFlameAnimationTime = 100;
    unsigned int m_jetFlameAnimationTimer = 0;
};


#endif //ASTEROIDS_PLAYER_H
