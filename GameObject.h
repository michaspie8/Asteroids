#ifndef ASTEROIDS_GAMEOBJECT_H
#define ASTEROIDS_GAMEOBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector.h"
#include <string>


class GameObject {
public:
    virtual void draw();

    virtual void update();

    virtual void clean();

    [[nodiscard]] bool isMarkedForDeletion() { return m_MarkedForDeletion; };

    GameObject(const LoaderParams *params);

    virtual ~GameObject() {};

    Vector2 getPosition() { return m_Position; };

    float getWidth() { return m_Width; };

    float getHeight() { return m_Height; };

    float getSpin() { return m_Spin; };

    float getAngle() { return m_Angle; };

    float getSpeed() { return m_Speed; };

    Vector2 getVelocity() { return m_Velocity; };

    Vector2 getAcceleration() { return m_Acceleration; };

    bool getCanMove() { return m_CanMove; };

    bool getCanShoot() { return m_CanShoot; };

    bool getIsMoving() { return m_IsMoving; };

    std::string getTextureId() { return m_TextureId; };

    void setPosition(Vector2 pos) { m_Position = pos; };

    void setWidth(float w) { m_Width = w; };

    void setHeight(float h) { m_Height = h; };

    void setSpin(float spin) { m_Spin = spin; };

    void setAngle(float angle) { m_Angle = angle; };

    void setSpeed(float speed) { m_Speed = speed; };

    void setVelocity(Vector2 velocity) { m_Velocity = velocity; };

    void setAcceleration(Vector2 acceleration) { m_Acceleration = acceleration; };

    void setCanMove(bool canMove) { m_CanMove = canMove; };

    void setCanShoot(bool canShoot) { m_CanShoot = canShoot; };

    void setIsMoving(bool isMoving) { m_IsMoving = isMoving; };

    void setTextureId(std::string textureId) { m_TextureId = textureId; };

    void setMarkedForDeletion(bool marked) { m_MarkedForDeletion = marked; };

    void printInfo();

protected:
    bool m_MarkedForDeletion;

    Vector2 m_Position;
    float m_Width;
    float m_Height;
    float m_Spin;

    float m_Angle;          // Heading
    float m_Speed;
    Vector2 m_Velocity;
    Vector2 m_Acceleration;

    bool m_CanMove;
    bool m_CanShoot;
    bool m_IsMoving;

    std::string m_TextureId;


};

#endif //ASTEROIDS_GAMEOBJECT_H