//
// Created by Michal on 27.12.2023.
//

#include <nanosvg/nanosvg.h>
#include "Vector.h"
#include <string>
#include <SDL2_gfxPrimitives_font.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_render.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Game.h"
#include "Mathf.h"

#include <cmath>

float Mathf::smoothDamp(float current, float target, float &currentVelocity, float smoothTime, float maxSpeed,
                        float deltaTime) {
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float num3 = 1.0f / (1.0f + num2 + 0.479999989f * num2 * num2 + 0.234999999f * num2 * num2 * num2);
    float num4 = current - target;
    float num5 = target;
    float num6 = maxSpeed * smoothTime;
    num4 = std::clamp(num4, -num6, num6);
    target = current - num4;
    float num7 = (currentVelocity + num * num4) * deltaTime;
    currentVelocity = (currentVelocity - num * num7) * num3;
    float num8 = target + (num4 + num7) * num3;
    if (num5 - current > 0.0f == num8 > num5) {
        num8 = num5;
        currentVelocity = (num8 - num5) / deltaTime;
    }
    return num8;
}

Vector2 Mathf::smoothDamp(Vector2 current, Vector2 target, Vector2 &currentVelocity, float smoothTime, float maxSpeed,
                          float deltaTime) {
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float num3 = 1.0f / (1.0f + num2 + 0.479999989f * num2 * num2 + 0.234999999f * num2 * num2 * num2);
    Vector2 vector = current - target;
    Vector2 vector2 = target;
    float num4 = maxSpeed * smoothTime;
    vector = clampMagnitude(vector, num4);
    target = current - vector;
    Vector2 vector3 = (currentVelocity + (vector * num)) * deltaTime;
    currentVelocity = (currentVelocity - (vector3 * num)) * num3;
    Vector2 vector4 = target + (vector + vector3) * num3;
    if ((vector2 - current).length() > 0.0f == (vector4 - vector2).length() > 0.0f) {
        vector4 = vector2;
        currentVelocity = (vector4 - vector2) / deltaTime;
    }
    return vector4;
}

float Mathf::smoothDampAngle(float current, float target, float &currentVelocity, float smoothTime, float maxSpeed,
                             float deltaTime) {
    target = current + Mathf::deltaAngle(current, target);
    return Mathf::smoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

float Mathf::deltaAngle(float current, float target) {
    float num = Mathf::repeat(target - current, 360.0f);
    if (num > 180.0f) {
        num -= 360.0f;
    }
    return num;
}

float Mathf::repeat(float t, float length) {
    return t - std::floor(t / length) * length;
}

float Mathf::clamp(float value, float min, float max) {
    return std::min(std::max(value, min), max);
}

float Mathf::bezier(float p0, float p1, float p2, float p3, float t) {
    //cube bezier curve
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;
    float p = uuu * p0;
    p += 3 * uu * t * p1;
    p += 3 * u * tt * p2;
    p += ttt * p3;
    return p;
}




//Gaussian blur implementation, get pixels from texture, blur them and return them back

Uint32 *Mathf::GaussianBlur(Uint32 *pixels, int width, int height, int radius, float sigma) {
    //create kernel
    int kernelSize = radius * 2 + 1;
    auto *kernel = new float[kernelSize];
    float sum = 0;
    for (int i = 0; i < kernelSize; i++) {
        kernel[i] = exp(-0.5f * (float)(i - radius) * (float)(i - radius) / (sigma * sigma));
        sum += kernel[i];
    }
    for (int i = 0; i < kernelSize; i++) {
        kernel[i] /= sum;
    }

    //create temp array
    auto *temp = new Uint32[width * height];
    for (int i = 0; i < width * height; i++) {
        temp[i] = pixels[i];
    }

    //horizontal pass
    for (int y = 0; y < height; y++) {
        for (int x = radius; x < width - radius; x++) {
            float r = 0, g = 0, b = 0;
            for (int i = -radius; i <= radius; i++) {
                Uint32 pixel = temp[y * width + x + i];
                r += (float)((pixel >> 16) & 0xFF) * kernel[i + radius];
                g += (float)((pixel >> 8) & 0xFF) * kernel[i + radius];
                b += (float)(pixel & 0xFF) * kernel[i + radius];
            }
            pixels[y * width + x] = ((int) r << 16) | ((int) g << 8) | (int) b;
        }
    }

    //vertical pass
    for (int y = radius; y < height - radius; y++) {
        for (int x = 0; x < width; x++) {
            float r = 0, g = 0, b = 0;
            for (int i = -radius; i <= radius; i++) {
                Uint32 pixel = pixels[(y + i) * width + x];
                r += (float)((pixel >> 16) & 0xFF) * kernel[i + radius];
                g += (float)((pixel >> 8) & 0xFF) * kernel[i + radius];
                b += (float)(pixel & 0xFF) * kernel[i + radius];
            }
            pixels[y * width + x] = ((int) r << 16) | ((int) g << 8) | (int) b;
        }
    }

    delete[] kernel;
    delete[] temp;
    return pixels;
}

Vector2 Mathf::RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle) {
    float x = pointToRotate.x - centerPoint.x;
    float y = pointToRotate.y - centerPoint.y;
    float rotatedX = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
    float rotatedY = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
    return Vector2(rotatedX + centerPoint.x, rotatedY + centerPoint.y);
}