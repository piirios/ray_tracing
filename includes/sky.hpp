#pragma once
#include "object.hpp"
#include <cmath>
#include <optional>
#include <iostream>

class Sky : public Object
{
private:
    Color color; // Couleur du ciel

public:
    // Constructeurs
    Sky(Color acolor); // Constructeur avec couleur fixe

    // Méthode pour récupérer la couleur du ciel
    Color get_color(Point point) override;

    // Méthode pour récupérer la normale au ciel
    Vector get_normal(Point point) override;

    // Méthode pour tester si un point intersecte le ciel
    std::optional<Point> intersect(Ray r) override;
};
