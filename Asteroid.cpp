//
// Created by Michal on 30.12.2023.
//

#include "Asteroid.h"
#include "Renderer.h"
#include "Motion.h"
#include "Game.h"


Asteroid::Asteroid(int size) : Component("Asteroid") {
    m_Size = size;
}


void Asteroid::draw() {
    if (!m_Enabled) return;
    //TODO draw asteroid
}

void Asteroid::update() {
    if (!m_Enabled) return;
    //set acceleration
    auto motion = gameObject->getComponent<Motion>();
    auto angle = gameObject->getTransform()->getAbsoluteAngle();
    motion->setVelocity(degToVector(angle) * motion->getSpeed());
}

void Asteroid::clean() {
    delete this;
}

void Asteroid::Destroy(Vector2 contactPoint) {
    if (m_Size == 1) {
        gameObject->setMarkedForDeletion(true);
    } else {
        auto pos = gameObject->getTransform()->getAbsolutePosition();
        auto angle = direction(pos, contactPoint).VectorToDeg();
        auto num = std::rand() % 3 + 2;
        float angleStep = 360 / num;

        for (int i = 1; i < num + 1; ++i) {
            auto asteroid = MakeNew(m_Size - 1, pos, angle + angleStep * i);
            Game::getInstance()->addGameObject(asteroid);
        }
        gameObject->setMarkedForDeletion(true);
    }
}


void Asteroid::setSize(int size) {
    m_Size = size;
}

int Asteroid::getSize() {
    return m_Size;
}


GameObject *Asteroid::MakeNew(int size, Vector2 pos, float angle = 0) {
    switch (size) {
        case 1:
            size = 2;
            break;
        case 2:
            size = 12;
            break;
        case 3:
            size = 32;
            break;
        default:
            return nullptr;
    }
    auto asteroid = new GameObject(new LoaderParams(pos, size, size, angle == 0 ? std::rand() % 360 : angle,
                                                    "asteroid-" + std::to_string(size), "Asteroid", "Asteroid"));
    asteroid->addComponent(new Motion());
    asteroid->addComponent(new Renderer("asteroid-" + std::to_string(size), RenderType::VECTOR));
    asteroid->addComponent(new Asteroid(size));
    asteroid->addComponent(new Collider(Vector2(size, size), Vector2(0, 0), "Asteroid", ColliderType::CIRCLE));
    return asteroid;
}

