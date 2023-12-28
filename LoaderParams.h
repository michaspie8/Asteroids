#ifndef ASTEROIDS_LOADERPARAMS_H
#define ASTEROIDS_LOADERPARAMS_H

#include "Vector.h"
#include <string>

// SDLGameObject
class LoaderParams {
public:
    LoaderParams(Vector2 pos, int w, int h, float angle, std::string id, float spin = 0, float speed = 0,
                 Vector2 velocity = {0, 0}, Vector2 acceleration = {0, 0}, bool marked = false) : m_Position(pos),
                                                                                                  m_Width(w),
                                                                                                  m_Height(h),
                                                                                                  m_Angle(angle),
                                                                                                  m_TextureId(id),
                                                                                                  m_Spin(spin),
                                                                                                  m_Speed(speed),
                                                                                                  m_Velocity(velocity),
                                                                                                  m_Acceleration(
                                                                                                          acceleration),
                                                                                                  m_MarkedForDeletion(
                                                                                                          marked) {};

    Vector2 m_Position;
    int m_Width;
    int m_Height;
    float m_Spin;

    float m_Angle;
    float m_Speed;
    Vector2 m_Velocity;
    Vector2 m_Acceleration;

    bool m_MarkedForDeletion;

    std::string m_TextureId;


};

#endif //ASTEROIDS_LOADERPARAMS_H