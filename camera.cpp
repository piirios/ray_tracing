#include "includes/camera.hpp"
#include "includes/utils.hpp"

Point Camera::get_left_upper_corner_point(int width, int height)
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