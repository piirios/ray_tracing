#include "includes/camera.hpp"
#include "includes/utils.hpp"
#include "includes/ray.hpp"
#include <cmath>
#include <iostream>

inline Point Camera::get_left_upper_corner_point()
{
    return origine + direction * distance - horizontal_vecteur * (viewport_width / 2.0) + vertical_vecteur * (viewport_height / 2.0);
}

Camera::Camera()
    : origine(0.0, 0.0, 0.0),
      direction(Vector::get_ex()),
      distance(1.0),
      horizontal_vecteur(Vector::get_ey()),
      vertical_vecteur(Vector::get_ez())
{
}

Camera::Camera(Point p, Vector d, double dist, int width, double ratio, double viewport_width)
    : origine(p),
      direction(d / d.norm()),
      distance(dist),
      width(width),
      viewport_width(viewport_width)
{
    Vector third_party = (fabs(direction.y) < 0.999) ? Vector(0, 1, 0) : Vector(1, 0, 0);

    horizontal_vecteur = direction * third_party;
    horizontal_vecteur = horizontal_vecteur / horizontal_vecteur.norm();

    vertical_vecteur = horizontal_vecteur * direction;
    vertical_vecteur = vertical_vecteur / vertical_vecteur.norm();

    height = static_cast<int>(width / ratio);
    viewport_height = viewport_width / ratio;

    delta_u = viewport_width / width;
    delta_v = viewport_height / height;
}

const inline double Camera::real_ratio() const
{
    return static_cast<double>(width) / height;
}

Point Camera::get_point(int i, int j)
{
    return get_left_upper_corner_point() + horizontal_vecteur * (i * delta_u) - vertical_vecteur * (j * delta_v);
}

Ray Camera::build_ray(int i, int j)
{

    Point viewport_point = get_point(i, j);

    Vector ray_direction = viewport_point - origine;
    return Ray(ray_direction / ray_direction.norm(), origine);
}
