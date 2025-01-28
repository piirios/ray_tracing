#pragma once
#include "utils.hpp"
#include "ray.hpp"
#include "object.hpp"
#include <optional>

class Ground : public Object
{
private:
    Color color1;
    Color color2;
    double cell_size;
    double height;

public:
    Ground(Color acolor1, Color acolor2, double cell_size, double aheight);

    Color get_color(Point point);
    Vector get_normal(Point point);
    std::optional<Point> intersect(Ray r);
};
