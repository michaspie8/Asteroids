//
// Created by Michal on 02.01.2024.
//

#ifndef ASTEROIDS_SHOOTER_H
#define ASTEROIDS_SHOOTER_H

#include "Component.h"
#include "LoaderParams.h"
#include "Vector.h"
#include "GameObject.h"


class Shooter : public Component {

public:
    Shooter(float fireRate = 0.1, int bulletSpeed = 1, int bulletDamage = 1, float reloadTime = 500,
            unsigned int maxBullets = 3, std::string name = "Shooter") : Component(name) {
        m_FireRate = fireRate;
        m_BulletSpeed = bulletSpeed;
        m_BulletDamage = bulletDamage;
        m_ReloadTime = reloadTime;
        m_MaxBullets = maxBullets;
    };

    ~Shooter() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void setFireRate(int fireRate);

    void setBulletSpeed(int bulletSpeed);

    void setBulletDamage(int bulletDamage);

    void setReloadTime(unsigned int reloadTime);

    void setMaxBullets(unsigned int maxBullets);

    unsigned int getReloadTime();

    unsigned int getMaxBullets();

    unsigned int getBullets();

    int getFireRate();

    int getBulletSpeed();

    int getBulletDamage();

    void shoot();

    GameObject *bullet();

protected:
    float m_FireRate;
    int m_BulletSpeed;
    int m_BulletDamage;
    bool m_CanShoot = true;
    //timer for reload
    float m_ReloadTime = 0.3;
    unsigned int m_MaxBullets = 10;
    unsigned int m_Bullets;
    float m_Timer = 0;

//    std::vector<GameObject *> m_BulletsObjects;
};


#endif //ASTEROIDS_SHOOTER_H
