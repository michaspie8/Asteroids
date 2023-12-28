#ifndef ASTEROIDS_VECTOR_H
#define ASTEROIDS_VECTOR_H

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#include <cmath>

class Vector2 {
public:
    float x;
    float y;

    Vector2();

    Vector2(float x, float y);

    float length() const;

    void normalise();


    Vector2 operator+(Vector2 &v2) const;

    Vector2 operator-(Vector2 &v2) const;

    Vector2 operator*(Vector2 &v2) const;

    Vector2 operator/(Vector2 &v2) const;


    Vector2 operator+(float value) const;

    Vector2 operator-(float value) const;

    Vector2 operator*(float scalar) const;

    Vector2 operator/(float scalar) const;


    void operator+=(Vector2 &v2);


    void operator*=(float scalar);

    void operator=(int value);


    double VectorToDeg() const {
        return atan2(y, x) * 180 / M_PI;
    }

    friend float degToRadian(float deg);

    friend Vector2 degToVector(float deg);

    friend Vector2 clampMagnitude(Vector2 vector, float maxLength);

};

Vector2 degToVector(float deg);

float degToRadian(float deg);

Vector2 clampMagnitude(Vector2 vector, float maxLength);

typedef Vector2 Vector2D;

#endif //ASTEROIDS_VECTOR_H