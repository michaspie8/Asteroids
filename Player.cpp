//
// Created by Michal on 27.12.2023.
//

#include "Player.h"
#include "Game.h"
#include <cmath>
#include "EventHandler.h"
#include "Mathf.h"
#include "TextureManager.h"
#include "Vector.h"
#include "Components/Renderer.h"
#include "Components/Motion.h"
#include "Components/Shooter.h"


Player::Player(const LoaderParams &params, float angleDampTime, float rotationSpeed) : GameObject(params) {
    this->angleDampTime = angleDampTime;
    this->rotationSpeed = rotationSpeed;
    addComponent(new Motion());
    addComponent(new Renderer("player", RenderType::VECTOR));
    addComponent(new Shooter());
    addComponent(new PlayerCollider(Vector2((float)params.m_Width, (float)params.m_Height), Vector2(0, 0), "Player",
                                    ColliderType::CIRCLE));
    TextureManager::getInstance()->loadVector("assets/bullet.svg", "bullet", true);
    TextureManager::getInstance()->loadVector("assets/player.svg", "player", true);
}

Player::Player() : Player(
        LoaderParams(Vector2((float)Game::getInstance()->getWindowWidth() / 2, (float)Game::getInstance()->getWindowHeight() / 2),
                         48, 48, 0, "player", "Player"),
        0.15f, 5) {

    //init jet flame
    TextureManager::getInstance()->loadVector("assets/jet-flame.svg", "jet-flame", true);
    //auto pos = getTransform()->getAbsolutePosition();
    Vector2 jetflamesize = {getTransform()->getWidth() * 8 * 0.09375f, getTransform()->getHeight() * 8 * 0.1875f};
    Vector2 jetflamePos = {(getTransform()->getWidth() / 2 + jetflamesize.x / 2),
                           (getTransform()->getHeight() / 2 - jetflamesize.y / 6)};
    m_JetFlame = new GameObject(
            LoaderParams(jetflamePos, (int)jetflamesize.x, (int)jetflamesize.y,
                             180, "jet-flame"));
    //beacuse he has a parent position is relative to parent, the pos above is just a shift to a right position
    m_JetFlame->setParent(this);
    m_JetFlame->addComponent(new Motion());
    m_JetFlame->addComponent(new Renderer("jet-flame", RenderType::VECTOR));
    //m_JetFlame->getComponent("Renderer")->setEnabled(false);
    Game::getInstance()->addGameObject(m_JetFlame);

}

Player::~Player() = default;

void Player::draw() {
    GameObject::draw();
}

void Player::update() {
    if (!m_Enabled) return;

    auto motion = getComponent<Motion>("Motion");
    auto jetRenderer = m_JetFlame->getComponent<Component>("Renderer");

    auto angle = getTransform()->getAngle();
    auto acceleration = motion->getAcceleration();
    auto velocity = motion->getVelocity();
    auto position = getTransform()->getPosition();

    //handle input
    int delta = EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_LEFT) -
                EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_RIGHT);

    if (EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_SPACE)) {
        getComponent<Shooter>("Shooter")->shoot();
    }

    //angle damping
    angle = Mathf::smoothDampAngle(angle, angle - (float)delta * rotationSpeed, angleDampVelocity, angleDampTime, 1000,
                                   (float)Game::getInstance()->getDeltaTime());

    //acceleration
    if (EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_UP)) {

        acceleration = degToVector(angle) * 0.1f;

//spawn jet flame -> position is applied in child game object automatically

        //todo animation of jet flame (two svg in texture map and switch between them when in half of animation time or sth)
        if (m_jetFlameAnimationTimer > m_jetFlameAnimationTime) {
            m_jetFlameAnimationTimer = 0;
            jetRenderer->setEnabled(!jetRenderer->isEnabled());
        } else {
            m_jetFlameAnimationTimer += Game::getInstance()->getDeltaTime();
        }

    } else {
        jetRenderer->setEnabled(false);

        acceleration = Vector2(0, 0);
    }
    velocity += acceleration;
    if (acceleration.length() < 0.1f) {
        velocity *= 0.99f;
    }

    //limit velocity
    if (velocity.length() > 10) {
        velocity.normalise();
        velocity *= 10;
    }
//apply changes
    getTransform()->setPosition(position);
    getTransform()->setAngle(angle);
    motion->setAcceleration(acceleration);
    motion->setVelocity(velocity);
    GameObject::update();
}

void Player::clean() {
    GameObject::clean();
}

void Player::OnCollisionEnter(GameObject *other) {
    if (other->getName() == "Asteroid") {
        //todo player death
        std::cout << "Player death" << std::endl;
    }
}


