#include "includes/sphere.hpp"
#include <cmath>
#include <optional>
#include <iostream>

// Constructeurs
Sphere::Sphere(Point acenter, float aradius)
    : center(acenter), radius(aradius) {}

Sphere::Sphere(Point acenter, float aradius, color_t acolor)
    : center(acenter), radius(aradius)
{
  color = acolor;
}

Sphere::Sphere(Point acenter, float aradius, char acolor)
    : center(acenter), radius(aradius)
{
  color = colorName(acolor);
}

// Méthode pour récupérer la couleur de la sphère
color_t Sphere::get_color(Point point)
{
  return color;
}

// Méthode pour récupérer la normale à la surface de la sphère en un point donné
Vector Sphere::get_normal(Point p)
{
  Vector v = p - center;
  if (v.norm() == 0)
  {
    return Vector(0.0, 0.0, 0.0); // Si le point est exactement au centre
  }
  return v / v.norm(); // Normalisation du vecteur
}

// Méthode pour tester si un point est sur la surface de la sphère
bool Sphere::on_surface(Point p)
{
  return (radius == (p - center).norm()); // Vérification de la distance au centre
}

// Méthode pour tester l'intersection avec un rayon
std::optional<Point> Sphere::intersect(Ray r)
{
  const std::optional<Point> None = std::nullopt;
  double a = r.vec.dot(r.vec);
  double b = 2 * (r.start - center).dot(r.vec);
  double c = (r.start - center).dot(r.start - center) - radius * radius;

  double discriminant = b * b - 4 * a * c; // Calcul du discriminant
  if (discriminant < 0)
  {
    return None; // Pas d'intersection
  }
  else if (discriminant == 0.0)
  {
    double t = -b / (2 * a);
    return Point(r.start.x + t * r.vec.x,
                 r.start.y + t * r.vec.y,
                 r.start.z + t * r.vec.z); // Une seule intersection
  }
  else
  {
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    Point p1(r.start.x + t1 * r.vec.x, r.start.y + t1 * r.vec.y,
             r.start.z + t1 * r.vec.z);
    Point p2(r.start.x + t2 * r.vec.x, r.start.y + t2 * r.vec.y,
             r.start.z + t2 * r.vec.z);

    if (t1 < 0)
    {
      return p2; // Choisit le point d'intersection le plus proche
    }
    else if (t2 < 0)
    {
      return p1;
    }
    else if ((r.start - p1).norm() < (r.start - p2).norm())
    {
      return p1;
    }
    else
    {
      return p2;
    }
  }
}
