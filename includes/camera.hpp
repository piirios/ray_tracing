#include "utils.hpp"

class Camera
{
public:
    Point origine;    // position de la caméra
    Vector direction; // orientation de la caméra
    float distance;   // distance

    Vector horizontal_vecteur; // vecteur dans le sens de l'horizontal de l'image
    Vector vertical_vecteur;   // vecteur dans le sens de la vertical de l'image

    // Remarque: (direction, horizontal_vecteur, vertical_vecteur) forment une base orthonormée de l'espace

    Point get_left_upper_corner_point(int width, int height);
    Camera();
    Camera(Point p, Vector d, float dist);
};