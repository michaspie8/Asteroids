//
// Created by Michal on 02.01.2024.
//

#include "Bullet.h"
#include "Game.h"
#include "Asteroid.h"
#include "Vector.h"

void Bullet::draw() {

}

void Bullet::update() {
    if (!m_Enabled) return;
    lifeTimer += Game::getInstance()->getDeltaTime();
    if (lifeTime >= 2) {
        gameObject->setMarkedForDeletion(true);
        m_Enabled = false;
        lifeTime = 0;
    }
}

void Bullet::clean() {
    delete this;
}

void Bullet::OnCollisionEnter(GameObject *other) {
    if (other->getName() == "Asteroid") {
        auto asteroid = other->getComponent<Asteroid>();
        asteroid->Destroy(gameObject->getTransform()->getAbsolutePosition());
        gameObject->setMarkedForDeletion(true);
    }
}

void Bullet::setSpeed(int speed) {
    m_Speed = speed;
}

void Bullet::setDamage(int damage) {
    m_Damage = damage;
}

int Bullet::getSpeed() {
    return m_Speed;
}

int Bullet::getDamage() {
    return m_Damage;
}


