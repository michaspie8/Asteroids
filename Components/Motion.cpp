//
// Created by Michal on 30.12.2023.
//

#include "Motion.h"
#include "../GameObject.h"
#include "../Game.h"

void Motion::draw() {}

void Motion::update() {
    if (!m_Enabled) return;

    //Here we can edit only these, because the rest will be calculated in overriden func or somewhere else in gameobject

    //Edit angle
    auto angle = gameObject->getTransform()->getAngle();
    //trying to keep angle between 0 and 360
    angle = (int) angle % 360 + (angle - (int) angle);
    if (angle < 0) {
        angle += 360;
    }
    if(m_StayInScreen){
        auto transform = gameObject->getTransform();
        auto position = transform->getPosition();
        if (position.x > (float) Game::getInstance()->getWindowWidth()) {
            position.x = 0;
        } else if (position.x < 0) {
            position.x = (float) Game::getInstance()->getWindowWidth();
        }
        if (position.y > (float) Game::getInstance()->getWindowHeight()) {
            position.y = 0;
        } else if (position.y < 0) {
            position.y = (float) Game::getInstance()->getWindowHeight();
        }
        transform->setPosition(position);
    }
    gameObject->getTransform()->setAngle(angle);
    gameObject->getTransform()->setPosition(gameObject->getTransform()->getPosition() + m_Velocity);
}

void Motion::clean() {
    Component::clean();
}

void Motion::setSpeed(float speed) {
    m_Speed = speed;
}

void Motion::setVelocity(Vector2 velocity) {
    m_Velocity = velocity;
}

void Motion::setAcceleration(Vector2 acceleration) {
    m_Acceleration = acceleration;
}

float Motion::getSpeed() const {
    return m_Speed;
}

Vector2 Motion::getVelocity() {
    return m_Velocity;
}

Vector2 Motion::getAcceleration() {
    return m_Acceleration;
}

void Motion::addVelocity(Vector2 velocity) {
    m_Velocity += velocity;
}

void Motion::addAcceleration(Vector2 acceleration) {
    m_Acceleration += acceleration;
}
