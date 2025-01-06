#pragma once
#include "object.hpp"
#include <cmath>
#include <optional>
#include <iostream>

class Ground : public Object {
private:
    color_t color; // Couleur du sol

public:
    // Constructeurs
    Ground(color_t acolor);  // Constructeur avec couleur fixe

    // Méthode pour récupérer la couleur du sol
    color_t get_color(Point point) override;

    // Méthode pour récupérer la normale au sol
    Vector get_normal(Point point) override;

    // Méthode pour tester si un point intersecte le sol
    std::optional<Point> intersect(Ray r) override;
};