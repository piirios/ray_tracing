#include "includes/camera.hpp"
#include "includes/utils.hpp"
#include "const.cpp"

Point Camera::get_left_upper_corner_point(int width, int height)
{
    return origine + direction + horizontal_vecteur * (width / 2) + vertical_vecteur * (height / 2);
}

Camera::Camera() : origine(.0, .0, .0), direction(Constant::e_x), distance(1.), horizontal_vecteur(Constant::e_y), vertical_vecteur(Constant::e_z) {}
Camera::Camera(Point p, Vector d, float dist) : origine(p), direction(d), distance(dist)
{
    horizontal_vecteur = Vector(.0, .0, .0);
    vertical_vecteur = Vector(.0, .0, .0);
}