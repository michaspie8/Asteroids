//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_MOTION_H
#define ASTEROIDS_MOTION_H

#include "Component.h"
#include "../LoaderParams.h"
#include "../Vector.h"

class Motion : public Component {
public:
    Motion(float speed = 0, Vector2 velocity = Vector2::Zero(),
           Vector2 acceleration = Vector2::Zero(), std::string name = "Motion", bool stayInScreen = true) : Component(name) {
        m_Velocity = velocity;
        m_Acceleration = acceleration;
        m_Speed = speed;
        m_StayInScreen = stayInScreen;
    };

    ~Motion() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void setSpeed(float speed);

    void setVelocity(Vector2 velocity);

    void setAcceleration(Vector2 acceleration);

    float getSpeed();

    Vector2 getVelocity();

    Vector2 getAcceleration();

    void addVelocity(Vector2 velocity);

    void addAcceleration(Vector2 acceleration);


protected:
    float m_Speed;
    Vector2 m_Velocity;
    Vector2 m_Acceleration;
    bool m_StayInScreen;
};


#endif //ASTEROIDS_MOTION_H
