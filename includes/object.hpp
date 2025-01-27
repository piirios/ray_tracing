#pragma once
#include "utils.hpp"
#include "ray.hpp"
#include <optional>

class Object
{
protected:
    Point origin;

public:
    virtual Color get_color(Point point)
    {
        return colorName('b');
    };
    virtual Vector get_normal(Point point)
    {
        return point - Point(0., 0., 0.);
    };
    virtual std::optional<Point> intersect(Ray r)
    {
        return std::nullopt;
    };
};