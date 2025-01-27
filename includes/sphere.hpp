#pragma once
#include "object.hpp"
#include <cmath>
#include <optional>
#include <iostream>

class Sphere : public Object
{
private:
    Point center; // Centre de la sphère
    float radius; // Rayon de la sphère
    Color color;  // Couleur de la sphère

public:
    // Constructeurs
    Sphere(Point acenter, float aradius);               // Constructeur sans couleur
    Sphere(Point acenter, float aradius, Color acolor); // Constructeur avec couleur
    Sphere(Point acenter, float aradius, char acolor);  // Constructeur avec couleur définie par un caractère

    // Méthode pour récupérer la couleur de la sphère
    Color get_color(Point point) override;

    // Méthode pour récupérer la normale à la surface de la sphère en un point donné
    Vector get_normal(Point point) override;

    // Méthode pour tester si un point est sur la surface de la sphère
    bool on_surface(Point p);

    // Méthode pour tester l'intersection avec un rayon
    std::optional<Point> intersect(Ray r) override;
};
