//
// Created by Michal on 30.12.2023.
//

#include "Asteroid.h"
#include "Renderer.h"
#include "Motion.h"
#include "../Game.h"


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
    auto motion =gameObject->getComponent<Motion>();
    auto angle = gameObject->getTransform()->getAbsoluteAngle();
    motion->setVelocity(degToVector(angle) * motion->getSpeed());
}


void Asteroid::Destroy(Vector2 contactPoint, float speed) {
    auto size = m_Size;
    if (size == 1) {
        gameObject->clean();
        return;
    } else {
        auto pos = gameObject->getTransform()->getAbsolutePosition();
        auto angle = direction(pos, contactPoint).VectorToDeg();
        auto num = std::rand() % 3 + 2;
        float angleStep = (float)360 / (float)num;

        for (int i = 1; i < num + 1; ++i) {
            auto asteroid = MakeNew(size - 1, pos, (float)angle + angleStep * (float)i, (std::ceil(speed) / (float)(size * 2)));
            Game::getInstance()->addGameObject(asteroid);
        }
        gameObject->clean();
    }
}


void Asteroid::setSize(int size) {
    m_Size = size;
}

int Asteroid::getSize() const{
    return m_Size;
}


GameObject *Asteroid::MakeNew(int size, Vector2 pos, float angle, float speed) {
    int w, h;
    switch (size) {
        case 1:
            h = 8;
            w = 8;
            break;
        case 2:
            w = 16;
            h = 16;
            break;
        case 3:
            w=32;
            h=32;
            break;
        default:
            return nullptr;
    }
    auto asteroid = new GameObject(LoaderParams(pos, w, h, angle == 0 ? std::rand() % 360 : angle,
                                                    "asteroid-" + std::to_string(size), "Asteroid", "Asteroid"));
    auto motion = asteroid->addComponent(new Motion(1));
    motion->setSpeed(speed);
    asteroid->addComponent(new Renderer("asteroid-" + std::to_string(size), RenderType::VECTOR));
    asteroid->addComponent(new Collider(Vector2((float)w*0.75, h*0.75), Vector2(0, 0), "Asteroid", ColliderType::CIRCLE));
    asteroid->addComponent(new Asteroid(size));
    return asteroid;
}

