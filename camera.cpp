#include "includes/camera.hpp"
#include "includes/utils.hpp"
#include "includes/ray.hpp"

inline Point Camera::get_left_upper_corner_point()
{
    return origine + direction + horizontal_vecteur * (width / 2.) + vertical_vecteur * (height / 2.);
}

Camera::Camera() : origine(.0, .0, .0), direction(Vector::get_ex()), distance(1.), horizontal_vecteur(Vector::get_ey()), vertical_vecteur(Vector::get_ez()) {}
Camera::Camera(Point p, Vector d, double dist, int width, double ratio, double viewport_width) : origine(p), direction(d), distance(dist), width(width), viewport_width(viewport_width)
{
    horizontal_vecteur = Vector(.0, .0, .0);
    vertical_vecteur = Vector(.0, .0, .0);

    height = int(width / ratio);

    viewport_height = viewport_width * double(width) / height; // use real ratio

    delta_u = viewport_width / width;
    delta_v = viewport_height / height;
}

const inline double Camera::real_ratio() const
{
    return double(width) / height;
}

Point Camera::get_point(int i, int j)
{
    return get_left_upper_corner_point() - vertical_vecteur * (delta_v * j) + horizontal_vecteur * (delta_u * i);
}

Ray Camera::build_ray(int i, int j)
{
    auto viewport_p = get_point(i, j);
    return Ray(viewport_p - origine, origine);
}