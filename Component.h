#ifndef ASTEROIDS_COMPONENT_H
#define ASTEROIDS_COMPONENT_H


#include <string>

//Forward declaration
class GameObject;

class Component {
public:
    //Add component and remove component adds or removes gameobject from component
    explicit Component(std::string name);

    //these method will be invoked by GameObject
    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void clean() = 0;

    //Game object that this component is attached to
    GameObject *gameObject = nullptr;

    std::string name;

    virtual ~Component() = default;

    void setEnabled(bool enabled) { Component::m_Enabled = enabled; }

    [[nodiscard]] bool isEnabled() const { return m_Enabled; }

    friend class GameObject;

protected:
    bool m_Enabled = true;
};

#endif //ASTEROIDS_COMPONENT_H