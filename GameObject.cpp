#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

GameObject::GameObject(const LoaderParams *params) {
    m_Position = params->m_Position;
    m_Width = params->m_Width;
    m_Height = params->m_Height;
    m_Spin = params->m_Spin;

    m_Angle = params->m_Angle;
    m_Speed = params->m_Speed;
    m_Velocity = params->m_Velocity;
    m_Acceleration = params->m_Acceleration;

    m_MarkedForDeletion = params->m_MarkedForDeletion;

    m_TextureId = params->m_TextureId;
}

void GameObject::draw() {
    TextureManager::getInstance()->drawFrameEx(m_TextureId, 0, 0, 512, 512, (int) m_Position.x, (int) m_Position.y,
                                               m_Width, m_Height, m_Spin);

}

void GameObject::update() {
    m_Velocity = degToVector(m_Angle) * m_Speed;
    m_Position += m_Velocity;
//    std::cout << m_Position.x<<", "<<m_Position.y<<"\n";
}

void GameObject::clean() {
    m_MarkedForDeletion = true;
}

void GameObject::printInfo() {
    std::cout << "Position: " << m_Position.x << ", " << m_Position.y << "\n";
    std::cout << "Width: " << m_Width << "\n";
    std::cout << "Height: " << m_Height << "\n";
    std::cout << "Spin: " << m_Spin << "\n";
    std::cout << "Angle: " << m_Angle << "\n";
    std::cout << "Speed: " << m_Speed << "\n";
    std::cout << "Velocity: " << m_Velocity.x << ", " << m_Velocity.y << "\n";
    std::cout << "Acceleration: " << m_Acceleration.x << ", " << m_Acceleration.y << "\n";
    std::cout << "Marked for deletion: " << m_MarkedForDeletion << "\n";
    std::cout << "Texture ID: " << m_TextureId << "\n";
}
