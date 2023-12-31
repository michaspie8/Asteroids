//
// Created by Michal on 27.12.2023.
//

#ifndef ASTEROIDS_MATHF_H
#define ASTEROIDS_MATHF_H

#include <algorithm>
#include "Vector.h"
#include <SDL.h>


class Mathf {
public:
    //Unity SmoothDamp implementation
    static float smoothDamp(float current, float target, float &currentVelocity, float smoothTime, float maxSpeed,
                            float deltaTime);

    static Vector2
    smoothDamp(Vector2 current, Vector2 target, Vector2 &currentVelocity, float smoothTime, float maxSpeed,
               float deltaTime);

    static float smoothDampAngle(float current, float target, float &currentVelocity, float smoothTime, float maxSpeed,
                                 float deltaTime);

    static float deltaAngle(float current, float target);

    static float repeat(float t, float length);

    static float clamp(float value, float min, float max);

    //cubic bezier curve
    static float bezier(float p0, float p1, float p2, float p3, float t);

    static Uint32 *GaussianBlur(Uint32 *pixels, int width, int height, int radius, float sigma);
};


#endif //ASTEROIDS_MATHF_H
