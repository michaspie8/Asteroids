//
// Created by Michal on 02.01.2024.
//

#ifndef ASTEROIDS_COLLIDER_H
#define ASTEROIDS_COLLIDER_H

#include "Component.h"
#include "Vector.h"
#include "Bullet.h"
#include "GameObject.h"
#include <vector>

enum ColliderType {
    BOX,
    CIRCLE
};

class Collider : public Component {

public:
    Collider(Vector2 size, Vector2 pos, std::string name = "Collider", ColliderType type = BOX);

    ~Collider() override = default;

    void clean() override;

    void update() override;

    void draw() override { };

    //you can add your own collision functions to this class
    virtual void onCollisionEnter(GameObject *other) {};

    virtual void onCollisionExit(GameObject *other) {};

protected:
    Vector2 m_Size;
    Vector2 m_Pos;
    ColliderType m_Type;
    bool m_Colliding = false;

};

/*class AsteroidCollider : public Collider{
public:
    AsteroidCollider(Vector2 size, Vector2 pos, std::string name = "AsteroidCollider", ColliderType type = BOX) : Collider(size, pos, name, type) {};
    void onCollisionEnter(GameObject* other) override {

    };
};*/

class BulletCollider : public Collider {
public:
    BulletCollider(Vector2 size, Vector2 pos, std::string name = "BulletCollider", ColliderType type = BOX) : Collider(
            size, pos, name, type) {};

    void onCollisionEnter(GameObject *other) override {

        gameObject->getComponent<Bullet>()->OnCollisionEnter(other);

    };

    void draw() override { Collider::draw(); };
    void update() override { Collider::update(); };
    void clean() override { Collider::clean(); };
};


#endif //ASTEROIDS_COLLIDER_H
