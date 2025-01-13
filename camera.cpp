#include "includes/camera.hpp"
#include "includes/utils.hpp"

Point Camera::get_left_upper_corner_point(int width, int height)
{
    return origine + direction + horizontal_vecteur * (width / 2.) + vertical_vecteur * (height / 2.);
}

Camera::Camera() : origine(.0, .0, .0), direction(Vector::get_ex()), distance(1.), horizontal_vecteur(Vector::get_ey()), vertical_vecteur(Vector::get_ez()) {}
Camera::Camera(Point p, Vector d, float dist) : origine(p), direction(d), distance(dist)
{
    horizontal_vecteur = Vector(.0, .0, .0);
    vertical_vecteur = Vector(.0, .0, .0);
}