//
// Created by Michal on 27.12.2023.
//

#include "Player.h"
#include "Game.h"
#include <cmath>
#include "EventHandler.h"
#include "Mathf.h"
#include "TextureManager.h"
#include "Colors.h"


Player::Player(const LoaderParams *params, float angleDampTime, float rotationSpeed) : GameObject(params) {
    this->angleDampTime = angleDampTime;
    this->rotationSpeed = rotationSpeed;
}

Player::Player() : Player(
        new LoaderParams(Vector2(Game::getInstance()->getWindowWidth() / 2, 0), 64, 64, 0, "player"),
        0.1f, 3) {

}

Player::~Player() = default;

void Player::draw() {
    TextureManager::getInstance()->loadVector("assets/player.svg", "player", true);
    TextureManager::getInstance()->drawVectorTexture("player", m_Position, m_Width, m_Height, m_Spin);
}

void Player::update() {
    //handle input
    int delta = EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_LEFT) -
                EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_RIGHT);

    //damping of angle
    m_Angle = Mathf::smoothDampAngle(m_Angle, m_Angle - delta * rotationSpeed, angleDampVelocity, angleDampTime, 1000,
                                     Game::getInstance()->getDeltaTime());
    //tring to keep angle between 0 and 360
    m_Angle = (int) m_Angle % 360 + (m_Angle - (int) m_Angle);
    if (m_Angle < 0) {
        m_Angle += 360;
    }
    //acceleration
    if (EventHandler::getInstance()->isKeyboardKeyDown(SDL_SCANCODE_UP)) {
        m_Acceleration = degToVector(m_Angle) * 0.1f;
    } else {
        m_Acceleration = Vector2(0, 0);
    }
    m_Velocity += m_Acceleration;
    if (m_Acceleration.length() < 00.1f) {
        m_Velocity *= 0.99f;
    }

    //limit velocity
    if (m_Velocity.length() > 10) {
        m_Velocity.normalise();
        m_Velocity *= 10;
    }

    //if player is gonna go out of screen, teleport him to the other side
    if (m_Position.x > Game::getInstance()->getWindowWidth()) {
        m_Position.x = 0;
    } else if (m_Position.x < 0) {
        m_Position.x = Game::getInstance()->getWindowWidth();
    }
    if (m_Position.y > Game::getInstance()->getWindowHeight()) {
        m_Position.y = 0;
    } else if (m_Position.y < 0) {
        m_Position.y = Game::getInstance()->getWindowHeight();
    }


    //update position
    m_Position += m_Velocity;
    m_Spin = m_Angle;
    printInfo();
}

void Player::clean() {
    GameObject::clean();
}
