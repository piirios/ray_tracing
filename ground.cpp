#include "includes/ground.hpp"
#include <cmath>

Ground::Ground(Color acolor1, Color acolor2, double cell_size, double aheight)
    : color1(acolor1), color2(acolor2), cell_size(cell_size), height(aheight) {}

Color Ground::get_color(Point point)
{
    int x_cell = static_cast<int>(std::floor(point.x / cell_size));
    int z_cell = static_cast<int>(std::floor(point.z / cell_size));

    bool is_white = (x_cell + z_cell) % 2 == 0;
    return is_white ? color1 : color2;
}

Vector Ground::get_normal(Point point)
{
    return Vector(0.0, 1.0, 0.0);
}

std::optional<Point> Ground::intersect(Ray r)
{
    if (r.vec.y >= 0)
        return std::nullopt;

    double t = (height - r.start.y) / r.vec.y;

    // Si t <= 0, l'intersection est derrière la caméra
    if (t <= 0)
        return std::nullopt;

    Point intersection(r.start.x + t * r.vec.x, height, r.start.z + t * r.vec.z);
    return intersection;
}
