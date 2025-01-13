#pragma once
#include "utils.hpp"

class Ray
{
public:
    Vector vec;
    Point start;

    Point at(double t);

    Ray(Vector vec, Point start);
};