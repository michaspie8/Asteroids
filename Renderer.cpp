//
// Created by Michal on 30.12.2023.
//

#include "Renderer.h"
#include "Game.h"


void Renderer::draw() {
    if (!m_Enabled) return;
    if (m_RenderType == RenderType::SPRITE) {
        //TODO decide how large the frame should be, and maybe use draw() when angle is 0
        TextureManager::getInstance()->drawFrameEx(m_TextureID, 0, 0, 512, 512,
                                                   gameObject->getTransform()->getPosition().x,
                                                   gameObject->getTransform()->getPosition().y,
                                                   gameObject->getTransform()->getWidth(),
                                                   gameObject->getTransform()->getHeight(),
                                                   gameObject->getTransform()->getAngle());
    } else {
        TextureManager::getInstance()->drawVectorTexture(m_TextureID, gameObject->getTransform()->getPosition(),
                                                         gameObject->getTransform()->getWidth(),
                                                         gameObject->getTransform()->getHeight(),
                                                         gameObject->getTransform()->getAngle());
    }
}

void Renderer::update() {
}

void Renderer::clean() {
    delete this;
}

void Renderer::setTextureId(std::string textureId) {
    m_TextureID = textureId;
}

void Renderer::setRenderType(RenderType renderType) {
    m_RenderType = renderType;
}

std::string Renderer::getTextureId() {
    return m_TextureID;
}

RenderType Renderer::getRenderType() {
    return m_RenderType;
}

