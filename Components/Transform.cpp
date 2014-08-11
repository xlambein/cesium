#include "Transform.hpp"

Transform::Transform() :
    x(0),
    y(0),
    angle(0)
{
}

Transform::Transform(float x_, float y_, float angle_) :
    x(x_),
    y(y_),
    angle(angle_)
{
}

Transform::~Transform() {}
