#include "ground.hpp"

// Constructeur du sol
Ground::Ground(color_t acolor) : color(acolor) {}

// Méthode pour récupérer la couleur du sol
color_t Ground::get_color(Point point) {
    return color;  // Le sol a une couleur uniforme
}

// Méthode pour récupérer la normale au sol (vecteur pointant vers le haut)
Vector Ground::get_normal(Point point) {
    return Vector(0.0, 1.0, 0.0);  // Le sol est "en bas", donc la normale pointe vers le haut
}

// Méthode pour tester si un rayon intersecte le sol
std::optional<Point> Ground::intersect(Ray r) {
    // Si le rayon pointe vers le haut (dy > 0) et son origine est au-dessus du sol,
    // alors il y aura une intersection à y = 0.
    if (r.vec.y <= 0) return std::nullopt;  // Le rayon doit être dirigé vers le bas
    double t = -r.start.y / r.vec.y;  // La hauteur du sol (y = 0)
    if (t <= 0) return std::nullopt;  // Si le rayon ne va pas vers le sol, il n'y a pas d'intersection
    return Point(r.start.x + t * r.vec.x, 0.0, r.start.z + t * r.vec.z);  // Intersection avec le sol
}
