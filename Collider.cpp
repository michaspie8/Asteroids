//
// Created by Michal on 02.01.2024.
//

#include "Collider.h"
#include "Game.h"

Collider::Collider(Vector2 size, Vector2 pos, std::string name, ColliderType type) : Component(name) {
    m_Size = size;
    m_Pos = pos;
    m_Type = type;
    Game::getInstance()->addCollider(this);
}

void Collider::clean() {
    Game::getInstance()->removeCollider(this);
    delete this;
}

void Collider::update() {
    //foreach collider
    for (auto &collider: Game::getInstance()->getColliders()) {
        if (collider == this) continue;
        //check if colliding
        bool colliding = false;
        switch (m_Type) {
            case BOX:
                colliding = m_Pos.x + m_Size.x > collider->m_Pos.x &&
                            m_Pos.x < collider->m_Pos.x + collider->m_Size.x &&
                            m_Pos.y + m_Size.y > collider->m_Pos.y &&
                            m_Pos.y < collider->m_Pos.y + collider->m_Size.y;
                break;
            case CIRCLE:
                colliding = (m_Pos - collider->m_Pos).length() < m_Size.x + collider->m_Size.x;
                break;
        }

        if (colliding) {
            onCollisionEnter(collider->gameObject);
            m_Colliding = true;
        } else {
            if (m_Colliding) {
                m_Colliding = false;
                onCollisionExit(collider->gameObject);
            }
        }
    }
}

