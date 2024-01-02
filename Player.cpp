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
#include "Renderer.h"
#include "Motion.h"
#include "Shooter.h"


Player::Player(LoaderParams *params, float angleDampTime, float rotationSpeed) : GameObject(params) {
    this->angleDampTime = angleDampTime;
    this->rotationSpeed = rotationSpeed;
    addComponent(new Motion());
    addComponent(new Renderer("player", RenderType::VECTOR));
    addComponent(new Shooter());
    TextureManager::getInstance()->loadVector("assets/player.svg", "player", true);
}

Player::Player() : Player(
        new LoaderParams(Vector2(Game::getInstance()->getWindowWidth() / 2, Game::getInstance()->getWindowHeight() / 2),
                         32, 32, 0, "player", "Player"),
        0.1f, 3) {

    //init jet flame
    TextureManager::getInstance()->loadVector("assets/jet-flame.svg", "jet-flame", true);
    m_JetFlame = new GameObject(
            new LoaderParams(Vector2(getTransform()->getWidth() / 2, -getTransform()->getHeight() / 2 + 12 + 6), 6, 12,
                             180, "jet-flame"));
    m_JetFlame->setParent(this);
    m_JetFlame->addComponent(new Renderer("jet-flame", RenderType::VECTOR));
    m_JetFlame->addComponent(new Motion());

    m_JetFlame->getComponent("Renderer")->setEnabled(false);
    Game::getInstance()->addGameObject(m_JetFlame);

}

Player::~Player() = default;

void Player::draw() {
    GameObject::draw();
}

void Player::update() {
    if (!m_Enabled) return;

    auto *motion = getComponent<Motion>("Motion");
    auto *jetRenderer = m_JetFlame->getComponent<Component>("Renderer");

    auto angle = getTransform()->getAngle();
    auto acceleration = motion->getAcceleration();
    auto velocity = motion->getVelocity();
    auto position = getTransform()->getPosition();

    //handle input
    int delta = EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_LEFT) -
                EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_RIGHT);

    //angle damping
    angle = Mathf::smoothDampAngle(angle, angle - delta * rotationSpeed, angleDampVelocity, angleDampTime, 1000,
                                   Game::getInstance()->getDeltaTime());

    //acceleration
    if (EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_UP)) {

        acceleration = degToVector(angle) * 0.1f;

//spawn jet flame -> position is applied in child game object automatically

        //todo animation of jet flame (two svg in texture map and switch between them when in half of animation time or sth)
        if (SDL_GetTicks64() - m_jetFlameAnimationTimer > m_jetFlameAnimationTime) {
            m_jetFlameAnimationTimer = SDL_GetTicks64();
            jetRenderer->setEnabled(!jetRenderer->isEnabled());
        }

    } else {
        jetRenderer->setEnabled(false);

        acceleration = Vector2(0, 0);
    }
    velocity += acceleration;
    if (acceleration.length() < 00.1f) {
        velocity *= 0.99f;
    }

    //limit velocity
    if (velocity.length() > 10) {
        velocity.normalise();
        velocity *= 10;
    }

    //if player is gonna go out of screen, teleport him to the other side
    if (position.x > Game::getInstance()->getWindowWidth()) {
        position.x = 0;
    } else if (position.x < 0) {
        position.x = Game::getInstance()->getWindowWidth();
    }
    if (position.y > Game::getInstance()->getWindowHeight()) {
        position.y = 0;
    } else if (position.y < 0) {
        position.y = Game::getInstance()->getWindowHeight();
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


