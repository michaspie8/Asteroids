//
// Created by Michal on 02.01.2024.
//

#include "Collider.h"

#include <utility>
#include "../Game.h"

//if circle, size.x is radius, and size.y can be 0
Collider::Collider(Vector2 size, Vector2 pos, std::string name, ColliderType type) : Component(std::move(name)) {
    m_Size = size;
    m_Pos = pos;
    m_Type = type;
    Game::getInstance()->addCollider(this);
}

void Collider::clean() {
    Game::getInstance()->removeCollider(this);
    Component::clean();
}

void Collider::update() {
    //update position, beacaouse position var is relative to transform
    auto pos = getPosition();
    //foreach collider
    auto colliders = Game::getInstance()->getColliders();
    for (auto collider : colliders) {
        if (collider == this) continue;

        auto otherPos = collider->getPosition();

        //check if colliding
        bool colliding = false;
        switch (m_Type) {
            case BOX:
                colliding = pos.x + m_Size.x > otherPos.x &&
                            pos.x < otherPos.x + collider->m_Size.x &&
                            pos.y + m_Size.y > otherPos.y &&
                            pos.y < otherPos.y + collider->m_Size.y;
                break;
            case CIRCLE:
                colliding = (pos - otherPos).length() < m_Size.x + collider->m_Size.x;
                break;
        }

        if (colliding) {
            onCollisionEnter(collider->gameObject);
            m_Colliding = true;
        }else{
            if(collider->m_Colliding){
                collider->onCollisionExit(gameObject);
                collider->m_Colliding = false;
            }
        }

        /*else {
            if (m_Colliding) {
                m_Colliding = false;
                onCollisionExit(collider->gameObject);
            }
        }*/
    }
}


