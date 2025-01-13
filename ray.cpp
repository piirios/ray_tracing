#include "includes/ray.hpp"
#include "includes/utils.hpp"

Point Ray::at(double t)
{
    return start + vec * t;
}

Ray::Ray(Vector vec, Point start) : vec(vec), start(start) {};