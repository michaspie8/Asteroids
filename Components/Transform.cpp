//
// Created by Michal on 30.12.2023.
//

#include "Transform.h"
#include "../GameObject.h"
#include "../LoaderParams.h"
#include "Component.h"

Transform::Transform(GameObject *gameObject, const LoaderParams &params) : Transform(params) {
    this->gameObject = gameObject;
}

Transform::Transform(const LoaderParams &params) : Component(params.m_Name) {
    m_Position = params.m_Position;
    m_Width = (float)params.m_Width;
    m_Height = (float)params.m_Height;
    m_Angle = params.m_Angle;
}

void Transform::draw() {

}

void Transform::update() {

}

void Transform::clean() {
    Component::clean();
}

void Transform::setPosition(Vector2 position) {
    m_Position = position;
}

void Transform::setWidth(float width) {
    m_Width = width;
}

void Transform::setHeight(float height) {
    m_Height = height;
}

void Transform::setAngle(float angle) {
    m_Angle = angle;
}

Vector2 Transform::getPosition() {
    return m_Position;
}

float Transform::getWidth() const {
    return m_Width;
}

Vector2 Transform::getAbsolutePosition() {
    if (gameObject->getParent() != nullptr) {
        return gameObject->getParent()->getTransform()->getAbsolutePosition() + m_Position;
    }
    return m_Position;
}

float Transform::getHeight() const {
    return m_Height;
}

float Transform::getAngle() const {
    return m_Angle;
}

float Transform::getAbsoluteAngle() {
    if (gameObject->getParent() != nullptr) {
        return gameObject->getParent()->getTransform()->getAbsoluteAngle() + m_Angle;
    }
    return m_Angle;
}



