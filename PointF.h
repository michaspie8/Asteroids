//
// Created by Michal on 28.12.2023.
//

#ifndef ASTEROIDS_POINTF_H
#define ASTEROIDS_POINTF_H


#include <cmath>


class PointF {

public:
    PointF(float x, float y) : x(x), y(y) {}

    PointF() : x(0), y(0) {}

    float x;
    float y;

    PointF operator+(const PointF &other) const {
        return PointF(x + other.x, y + other.y);
    }

    PointF operator-(const PointF &other) const {
        return PointF(x - other.x, y - other.y);
    }

    PointF operator*(const float &other) const {
        return PointF(x * other, y * other);
    }

    PointF operator/(const float &other) const {
        return PointF(x / other, y / other);
    }

    PointF operator+=(const PointF &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    PointF operator-=(const PointF &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    PointF operator*=(const float &other) {
        x *= other;
        y *= other;
        return *this;
    }

    PointF operator/=(const float &other) {
        x /= other;
        y /= other;
        return *this;
    }

    bool operator==(const PointF &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const PointF &other) const {
        return x != other.x || y != other.y;
    }

    PointF operator-() const {
        return PointF(-x, -y);
    }

    float length() const {
        return sqrt(x * x + y * y);
    }

    float lengthSquared() const {
        return x * x + y * y;
    }

    void normalise() {
        float len = length();
        x /= len;
        y /= len;
    }

    PointF normalised() const {
        float len = length();
        return PointF(x / len, y / len);
    }

    float dot(const PointF &other) const {
        return x * other.x + y * other.y;
    }

    float cross(const PointF &other) const {
        return x * other.y - y * other.x;
    }

    float angle() const {
        return atan2(y, x);
    }

    float angle(const PointF &other) const {
        return atan2(cross(other), dot(other));
    }

    PointF project(const PointF &other) const {
        return other * (dot(other) / other.lengthSquared());
    }

    PointF perpendicular() const {
        return PointF(-y, x);
    }


};


#endif //ASTEROIDS_POINTF_H
