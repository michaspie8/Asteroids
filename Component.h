//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_COMPONENT_H
#define ASTEROIDS_COMPONENT_H

#include "GameObject.h"
#include <string>
#include "Game.h"


class Component {

public:

    Component(GameObject *gameObject, std::string name) : name(name), gameObject(gameObject) {};

    //these method will be invoked by GameObject
    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void clean() { delete this; }

    //Game object that this component is attached to
    GameObject *gameObject;

    std::string name;

    virtual ~Component() = default;

    void setEnabled(bool enabled) { Component::m_Enabled = enabled; }

    [[nodiscard]] bool isEnabled() const { return m_Enabled; }

protected:
    bool m_Enabled = true;
};

#endif //ASTEROIDS_COMPONENT_H