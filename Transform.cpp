//
// Created by Michal on 30.12.2023.
//

#include "Transform.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "Component.h"

void Transform::draw() {

}

void Transform::update() {

}

void Transform::clean() {

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

float Transform::getWidth() {
    return m_Width;
}

Vector2 Transform::getAbsolutePosition() {
    if (gameObject->getParent() != nullptr) {
        return m_pParent->getTransform()->getPosition() + m_Position;
    }
    return m_Position;
}

float Transform::getHeight() {
    return m_Height;
}

float Transform::getAngle() {
    return m_Angle;
}

float Transform::getAbsoluteAngle() {
    if (gameObject->getParent() != nullptr) {
        return m_pParent->getTransform()->getAngle() + m_Angle;
    }
    return m_Angle;
}

