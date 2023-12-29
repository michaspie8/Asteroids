//
// Created by Michal on 28.12.2023.
//

#ifndef ASTEROIDS_CHILDGAMEOBJECT_H
#define ASTEROIDS_CHILDGAMEOBJECT_H

#include "GameObject.h"


//Game object that is a child of another game object
class ChildGameObject : public GameObject {

public:
    ChildGameObject(const LoaderParams *params, GameObject *parent);

    ~ChildGameObject() override;

    void draw() override;

    void update() override;

    void clean() override;

    void setParent(GameObject *parent) { m_pParent = parent; }

    //Set position now sets relative position, so it can be used to set position relative to parent
    void setPosition(Vector2 position) { relativePosition = position; }

    void setRelativeAngle(float angle) { relativeAngle = angle; }

    GameObject *getParent() const { return m_pParent; }

    Vector2 getRelativePosition() const { return relativePosition; }

    float getRelativeAngle() const { return relativeAngle; }

protected:
    Vector2 relativePosition;
    float relativeAngle;
    GameObject *m_pParent;
};


#endif //ASTEROIDS_CHILDGAMEOBJECT_H
