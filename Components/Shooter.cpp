//
// Created by Michal on 02.01.2024.
//

#include "Shooter.h"
#include "Motion.h"
#include "Renderer.h"
#include "SDL.h"
#include "Bullet.h"
#include "Collider.h"
#include "Asteroid.h"
#include "../Game.h"
#include "../Mathf.h"

void Shooter::draw() {

}

void Shooter::update() {
    if (!m_Enabled) return;
    //time since last shot
    if (!m_CanShoot) {

        m_Timer += Game::getInstance()->getDeltaTime();
        //if there are bullets and the time since last shot is greater than fire rate, you can shoot
        std::cout << m_Bullets << std::endl;
        if (m_Bullets > 0) {
            //std::cout << m_Timer ;
            if (m_Timer >= m_FireRate) {
                //if there are bullets and the time since last shot is greater than fire rate, you can shoot
                m_CanShoot = true;
            }
        } else {
            //if the time since last shot is greater than reload time, you can reload and have max bullets
            //aka if you hadn't shot in time of reload time, you can shoot
            if (m_Timer >= m_ReloadTime) {
                m_Bullets = m_MaxBullets;
                m_CanShoot = true;
            }
        }

    }


}

void Shooter::clean() {
    Component::clean();
}

void Shooter::setFireRate(int fireRate) {
    m_FireRate = fireRate;
}

void Shooter::setBulletSpeed(int bulletSpeed) {
    m_BulletSpeed = bulletSpeed;
}

void Shooter::setBulletDamage(int bulletDamage) {
    m_BulletDamage = bulletDamage;
}

void Shooter::setReloadTime(unsigned int reloadTime) {
    m_ReloadTime = reloadTime;
}

void Shooter::setMaxBullets(unsigned int maxBullets) {
    m_MaxBullets = maxBullets;
}

unsigned int Shooter::getReloadTime() {
    return m_ReloadTime;
}

unsigned int Shooter::getMaxBullets() {
    return m_MaxBullets;
}

unsigned int Shooter::getBullets() {
    return m_Bullets;
}


int Shooter::getFireRate() {
    return m_FireRate;
}

int Shooter::getBulletSpeed() {
    return m_BulletSpeed;
}

int Shooter::getBulletDamage() {
    return m_BulletDamage;
}

void Shooter::shoot() {
    if (!m_CanShoot) return;
    m_CanShoot = false;
    m_Bullets--;
    m_Timer = 0;
    auto bullet = this->bullet();
    Game::getInstance()->addGameObject(bullet);
}

GameObject *Shooter::bullet() {
    auto pos = gameObject->getTransform()->getAbsolutePosition();
    auto angle = gameObject->getTransform()->getAbsoluteAngle();
    pos += {gameObject->getTransform()->getWidth() / 2, 0};
    pos = Mathf::RotatePoint(pos, gameObject->getTransform()->getAbsolutePosition(), angle);
    float s = std::ceil(gameObject->getTransform()->getWidth() / 4);
    auto bullet = new GameObject(LoaderParams(pos, s, s, 0, "bullet", "Bullet"));
    bullet->getTransform()->setAngle(angle);
    bullet->addComponent(new Motion());
    bullet->addComponent(new Renderer("bullet", RenderType::VECTOR));
    auto bullet_c = bullet->addComponent(new Bullet(m_BulletSpeed, m_BulletDamage));
    auto shooterVel = std::ceil(gameObject->getComponent<Motion>()->getVelocity().length());
    if (shooterVel < 2) {
        shooterVel = 2;
    }
    bullet_c->setSpeed(m_BulletSpeed + shooterVel);
    bullet->addComponent(new BulletCollider({s, s}, {0, 0}, "Bullet", ColliderType::CIRCLE));
    return bullet;
}