#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include "Transform.h"

GameObject::GameObject(LoaderParams *params) {
    m_Components = std::vector<Component *>();
    m_pTransform = new Transform(this, params);
    m_MarkedForDeletion = params->m_MarkedForDeletion;
    m_Name = params->m_Name;
    m_Tag = params->m_Tag;
    m_Enabled = params->m_Enabled;
}

void GameObject::draw() {
    //call draw on all components
    for (auto component: m_Components) {
        component->draw();
    }

}

void GameObject::update() {
    //call update on all components
    for (auto component: m_Components) {
        component->update();
    }
}

void GameObject::clean() {
    m_MarkedForDeletion = true;
    //call clean on all components
    for (auto component: m_Components) {
        component->clean();
    }

}

Component *GameObject::getComponent(std::string name) {
    for (auto component: m_Components) {
        if (component->name == name) {
            return component;
        }
    }
    return nullptr;
}



