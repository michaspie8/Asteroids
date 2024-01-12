//
// Created by Michal on 30.12.2023.
//

#include "Renderer.h"

#include <utility>
#include "../Game.h"


void Renderer::draw() {
    if (!m_Enabled) return;
    auto angle = gameObject->getTransform()->getAbsoluteAngle();
    auto pos = gameObject->getTransform()->getAbsolutePosition();

    if (m_RenderType == RenderType::SPRITE) {
        //TODO decide how large the frame should be, and maybe use draw() when angle is 0
        TextureManager::getInstance()->drawFrameEx(m_TextureID, 0, 0, 512, 512,
                                                   (int)pos.x,
                                                   (int)pos.y,
                                                   (int)gameObject->getTransform()->getWidth(),
                                                   (int)gameObject->getTransform()->getHeight(),
                                                   angle);
    } else {
        TextureManager::getInstance()->drawVectorTexture(m_TextureID, getRenderPositionVector(), angle,
                                                         gameObject->getTransform()->getWidth(),
                                                         gameObject->getTransform()->getHeight(),
                                                         getRenderRotationVector());
    }
}

void Renderer::update() {
}

void Renderer::clean() {
    Component::clean();
}

void Renderer::setTextureId(std::string textureId) {
    m_TextureID = std::move(textureId);
}

void Renderer::setRenderType(RenderType renderType) {
    m_RenderType = renderType;
}

void Renderer::setRenderRotation(RenderRotation renderRotation) {
    m_RenderRotation = renderRotation;
}

void Renderer::setRenderPosition(RenderPosition renderPosition) {
    m_RenderPosition = renderPosition;
}

RenderRotation Renderer::getRenderRotation() {
    return m_RenderRotation;
}

RenderPosition Renderer::getRenderPosition() {
    return m_RenderPosition;
}

Vector2 Renderer::getRenderPositionVector() {
    auto pos = gameObject->getTransform()->getAbsolutePosition();
    auto width = gameObject->getTransform()->getWidth();
    auto height = gameObject->getTransform()->getHeight();
    switch (m_RenderPosition) {
        case RenderPosition::CENTER:
            return Vector2(pos.x - width / 2, pos.y - height / 2);
        case RenderPosition::TOP_LEFT:
            return Vector2(pos.x, pos.y);
        case RenderPosition::TOP_RIGHT:
            return Vector2(pos.x - width, pos.y);
        case RenderPosition::BOTTOM_LEFT:
            return Vector2(pos.x, pos.y - height);
        case RenderPosition::BOTTOM_RIGHT:
            return Vector2(pos.x - width, pos.y - height);
        default:
            //circle is default
            return Vector2(pos.x - width / 2, pos.y - height / 2);
    }
}

//Rotation pivot:
Vector2 Renderer::getRenderRotationVector() {

    if (gameObject->getParent() != nullptr) {
        switch (m_RenderRotation) {
            case RenderRotation::PARENT:
                return gameObject->getParent()->getTransform()->getAbsolutePosition();
            case RenderRotation::OBJECT:
                return gameObject->getTransform()->getPosition();
            case RenderRotation::OBJECT_ABSOLUTE:
                return gameObject->getTransform()->getAbsolutePosition();
        }
    }


    switch (m_RenderRotation) {
        case RenderRotation::OBJECT:
            return gameObject->getTransform()->getPosition();
        default:
            return gameObject->getTransform()->getAbsolutePosition();
    }
}

std::string Renderer::getTextureId() {
    return m_TextureID;
}

RenderType Renderer::getRenderType() {
    return m_RenderType;
}

