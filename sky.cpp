#include "includes/sky.hpp"

// Constructeur du ciel
Sky::Sky(Color acolor) : color(acolor) {}

// Méthode pour récupérer la couleur du ciel
Color Sky::get_color(Point point)
{
    return color; // Le ciel a une couleur uniforme
}

// Méthode pour récupérer la normale au ciel (vecteur pointant vers le bas)
Vector Sky::get_normal(Point point)
{
    return Vector(0.0, -1.0, 0.0); // Le ciel est "au-dessus", donc la normale pointe vers le bas
}

// Méthode pour tester si un rayon intersecte le ciel
std::optional<Point> Sky::intersect(Ray r)
{
    // Si le rayon pointe vers le bas (dy < 0) et son origine est en dessous du ciel,
    // alors il y aura une intersection à une certaine hauteur.
    if (r.vec.y >= 0)
        return std::nullopt;                   // Le rayon doit être dirigé vers le bas
    double t = (1000.0 - r.start.y) / r.vec.y; // La hauteur du ciel (ici à y = 1000)
    if (t <= 0)
        return std::nullopt;                                                // Si le rayon ne va pas vers le ciel, il n'y a pas d'intersection
    return Point(r.start.x + t * r.vec.x, 1000.0, r.start.z + t * r.vec.z); // Intersection avec le ciel
}
