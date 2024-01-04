//
// Created by Michal on 02.01.2024.
//

#include "Bullet.h"
#include "../Game.h"
#include "Asteroid.h"
#include "../Vector.h"
#include "Motion.h"

void Bullet::draw() {

}

void Bullet::update() {
    if (!m_Enabled) return;
    m_LifeTimer += Game::getInstance()->getDeltaTime();
    auto motion = gameObject->getComponent<Motion>();
    auto transform = gameObject->getTransform();
    motion->setVelocity(degToVector(transform->getAngle()) * m_Speed);
    if (m_LifeTimer >= m_LifeTime) {
        gameObject->clean();
        m_Enabled = false;
        m_LifeTime = 0;
    }
    auto position = transform->getPosition();
    if (position.x > Game::getInstance()->getWindowWidth()) {
        position.x = 0;
    } else if (position.x < 0) {
        position.x = Game::getInstance()->getWindowWidth();
    }
    if (position.y > Game::getInstance()->getWindowHeight()) {
        position.y = 0;
    } else if (position.y < 0) {
        position.y = Game::getInstance()->getWindowHeight();
    }
    transform->setPosition(position);
}

void Bullet::clean() {
    Component::clean();
}

void Bullet::OnCollisionEnter(GameObject *other) {
    if (other->getName() == "Asteroid") {
        auto asteroid = other->getComponent<Asteroid>();
        asteroid->Destroy(gameObject->getTransform()->getAbsolutePosition());
        gameObject->clean();
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


