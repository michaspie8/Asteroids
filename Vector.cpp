#include "Vector.h"
#include <cmath>

Vector2::Vector2() {
    x = 0;
    y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2::length() const {
    return sqrt(x * x + y * y);
}

void Vector2::normalise() {
    if (length() > 0)
        *this *= 1 / length();
}

Vector2 clampMagnitude(Vector2 vector, float maxLength) {
    if (vector.length() > maxLength) {
        vector.normalise();
        vector *= maxLength;
    }
    return vector;
}

void Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
}


Vector2 Vector2::operator/(Vector2 v2) const {
    return {x / v2.x, y / v2.y};
}

Vector2 Vector2::operator+(Vector2 v2) const {
    return {x + v2.x, y + v2.y};
}

Vector2 Vector2::operator-(Vector2 v2) const {
    return {x - v2.x, y - v2.y};
}

Vector2 Vector2::operator*(Vector2 v2) const {
    return {x * v2.x, y * v2.y};
}

Vector2 Vector2::operator+(float value) const {
    return {x + value, y + value};
}

Vector2 Vector2::operator-(float value) const {
    return {x - value, y - value};
}

Vector2 Vector2::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vector2 Vector2::operator/(float scalar) const {
    return {x / scalar, y / scalar};
}


void Vector2::operator+=(Vector2 &v2) {
    x += v2.x;
    y += v2.y;
}


Vector2 &Vector2::operator=(float value) {
    x = value;
    y = value;
    return *this;
}


float degToRadian(float deg) {
    return deg * M_PI / 180;
}

Vector2 degToVector(float deg) {

    Vector2 vec(cos(degToRadian(deg)), sin(degToRadian(deg)));
    vec.normalise();
    return vec;
}

float Vector2::lengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::normalised() const {
    Vector2 vec(x, y);
    vec.normalise();
    return vec;
}


