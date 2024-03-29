#ifndef ASTEROIDS_GAMEOBJECT_H
#define ASTEROIDS_GAMEOBJECT_H

#include "LoaderParams.h"
#include "Vector.h"
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Components/Component.h"
#include "Components/Transform.h"


class GameObject {
public:
    explicit GameObject(const LoaderParams &params);


    virtual void draw();

    virtual void update();

    virtual void clean();

    [[nodiscard]] bool isMarkedForDeletion() const { return m_MarkedForDeletion; };

    virtual ~GameObject() = default;

    std::string getName() { return m_Name; };

    std::string getTag() { return m_Tag; };

    bool isEnabled() const { return m_Enabled; };

    Component *getComponent(const std::string& name);

    Transform *getTransform() { return m_pTransform; };

    //by type
    template<typename T>
    T *getComponent() {
        for (auto &component: m_Components) {
            if (dynamic_cast<T *>(component) != nullptr) {
                return dynamic_cast<T *>(component);
            }
        }
        return nullptr;
    }

    //type by name
    template<typename T>
    T *getComponent(std::string name) {
        for (auto &component: m_Components) {
            if (dynamic_cast<T *>(component) != nullptr && component->name == name) {
                return dynamic_cast<T *>(component);
            }
        }
        return nullptr;
    }


    GameObject *getParent() { return m_pParent; };

    //setters

    //add component adds any class deriving from component to this game object and sets its parent to this game object
    //use casting to cast t to Component*
    template<typename T>
    T *addComponent(T *t) {
        auto c = dynamic_cast<Component *>(t);
        if (c == nullptr) throw std::invalid_argument("T must derive from Component");
        m_Components.push_back(c);
        c->gameObject = this;
        return t;
    }

    Component *addComponent(Component *c) {
        m_Components.push_back(c);
        c->gameObject = this;
        return c;
    }


    //You have to delete component by calling Component::clean() or GameObject::clean(),
    //because this only deletes a pointer to component, it doesnt free memory from heap
    void removeComponent(Component *c) {
        for (int i = 0; i < m_Components.size(); i++) {
            if (m_Components[i] == c) {
                m_Components.erase(m_Components.begin() + i);
                return;
            }
        }
    }

    template<class T>
    void removeComponent(T *component) {
        auto c = dynamic_cast<Component *>(component);
        if (c == nullptr) return throw std::invalid_argument("T must derive from Component");
        removeComponent(c);
    }


    void setMarkedForDeletion(bool marked) { m_MarkedForDeletion = marked; };


    void setName(std::string name) { m_Name = std::move(name); };

    void setTag(std::string tag) { m_Tag = std::move(tag); };

    void setEnabled(bool enabled) { m_Enabled = enabled; };

    //change parent of this game object
    void setParent(GameObject *parent) { m_pParent = parent; };

protected:

    //Game class uses this to safely delete game objects
    bool m_MarkedForDeletion;
    //if false, this game object (so all of its components) will not be updated or drawn
    bool m_Enabled;
    //name of this object, it's not texture id
    std::string m_Name;
    //tag is used to identify game objects
    //for example, all asteroids have tag "asteroid"
    //or player has tag "player"
    //it doen't have to be unique,
    // beacause of the getComponentS method
    std::string m_Tag;

    //all components of this game object
    std::vector<Component *> m_Components;
    //parent of this game object, nullptr if none
    GameObject *m_pParent = nullptr;
    //its just a shortcut to transform component, beacuse its in every game object
    Transform *m_pTransform = nullptr;

};

#endif //ASTEROIDS_GAMEOBJECT_H