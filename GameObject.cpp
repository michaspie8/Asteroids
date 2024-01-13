#include "GameObject.h"
#include "TextureManager.h"
#include "Components/Transform.h"

GameObject::GameObject( const LoaderParams& params) {
    m_Components = std::vector<Component *>();
    m_pTransform = new Transform(params);
    addComponent<Transform>(m_pTransform);
    m_MarkedForDeletion = params.m_MarkedForDeletion;
    m_Name = params.m_Name;
    m_Tag = params.m_Tag;
    m_Enabled = params.m_Enabled;
}

void GameObject::draw() {
    //call draw on all components
    for (auto &component: m_Components) {
        component->draw();
    }
}

void GameObject::update() {
    //call update on all components
    for (int i = 0; i < m_Components.size(); i++) {
        auto &component = m_Components[i];
        component->update();
    }
}

void GameObject::clean() {
    m_MarkedForDeletion = true;
    //call clean on all components
    auto temp = m_Components;
    for (auto &component: temp) {
        component->clean();
    }

}

Component *GameObject::getComponent(const std::string& name) {
    for (int i = 0; i < m_Components.size(); i++) {
        auto &component = m_Components[i];
        if (component->name == name) {
            return component;
        }
    }
    return nullptr;
}





