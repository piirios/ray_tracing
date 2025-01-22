#include "utils.hpp"
#include "ray.hpp"

class Camera
{
private:
    double delta_u;
    double delta_v;

    double viewport_width;
    double viewport_height;

    inline Point get_point(int i, int j);

public:
    Point origine;    // position de la caméra
    Vector direction; // orientation de la caméra
    double distance;  // distance

    int width;
    int height;

    Vector horizontal_vecteur; // vecteur dans le sens de l'horizontal de l'image
    Vector vertical_vecteur;   // vecteur dans le sens de la vertical de l'image

    // Remarque: (direction, horizontal_vecteur, vertical_vecteur) forment une base orthonormée de l'espace

    inline Point get_left_upper_corner_point();
    Camera();
    Camera(Point p, Vector d, double dist, int width, double ratio, double viewport_width);

    const inline double real_ratio() const; // permet de récupérer le ratio réel

    Ray build_ray(int i, int j); // permet de construire le rayon pour le pixel au (i, j)
};