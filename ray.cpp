#include "includes/ray.hpp"

Point Ray::at(double t)
{
    return start + vec * t;
}