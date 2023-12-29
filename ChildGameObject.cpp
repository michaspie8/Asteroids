//
// Created by Michal on 28.12.2023.
//

#include "ChildGameObject.h"
#include "TextureManager.h"

ChildGameObject::ChildGameObject(const LoaderParams *params,
                                 GameObject *parent) : GameObject(params), m_pParent(parent) {
    relativePosition = m_Position;
    relativeAngle = m_Angle;
}
/*
TODO fix this, i wanted to make us able to make a child game object from a game object, but its really complicated
ChildGameObject::ChildGameObject(GameObject *obj, GameObject *parent) : GameObject(obj), m_pParent(parent) {
}*/


ChildGameObject::~ChildGameObject() = default;

void ChildGameObject::draw() {
    if(!m_renderable){
        return;
    }
    //calculate angle and position again, because parent can change after last update
    //parent position is added to child position
    m_Position = m_pParent->getPosition() + relativePosition;
    //parent angle is added to child angle
    m_Angle = m_pParent->getAngle() + relativeAngle;
    //p is parent position
    auto p = m_pParent->getPosition();
    TextureManager::getInstance()->drawVectorTexture(m_TextureId, m_Position, m_Width, m_Height, m_Angle, PointF(p.x, p.y));
}

void ChildGameObject::update() {
    //check if parent is not null
    if (m_pParent == nullptr) {
        //if so delete this object
        m_MarkedForDeletion = true;
    }
    //parent position is added to child position
    m_Position = m_pParent->getPosition() + relativePosition;
    //parent angle is added to child angle
    m_Angle = m_pParent->getAngle() + relativeAngle;
    printInfo();
    GameObject::update();
}

void ChildGameObject::clean() {
    GameObject::clean();
}


