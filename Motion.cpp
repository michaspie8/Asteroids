//
// Created by Michal on 30.12.2023.
//

#include "Motion.h"
#include "GameObject.h"

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
    gameObject->getTransform()->setAngle(angle);
    gameObject->getTransform()->setPosition(gameObject->getTransform()->getPosition() + m_Velocity);
}

void Motion::clean() {
    delete this;
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

float Motion::getSpeed() {
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
