//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_TRANSFORM_H
#define ASTEROIDS_TRANSFORM_H

#include "Component.h"

class Transform : public Component {

public:
    Transform(GameObject *gameObject, LoaderParams *params) : Component(gameObject, params->m_Name) {
        m_Position = params->m_Position;
        m_Width = params->m_Width;
        m_Height = params->m_Height;
        m_Angle = params->m_Angle;
    };

    ~Transform() override = default;

    void draw() override;

    void update() override;

    void clean() override;


    void setPosition(Vector2 position);

    void setWidth(float width);

    void setHeight(float height);

    void setAngle(float angle);

    Vector2 getPosition();

    Vector2 getAbsolutePosition();

    float getWidth();

    float getHeight();

    float getAngle();

    float getAbsoluteAngle();


protected:
    Vector2 m_Position;
    float m_Width;
    float m_Height;
    float m_Angle;

};


#endif //ASTEROIDS_TRANSFORM_H
