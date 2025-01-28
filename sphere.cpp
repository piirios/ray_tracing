#include "includes/sphere.hpp"
#include <cmath>
#include <optional>
#include <iostream>

Sphere::Sphere(Point acenter, float aradius)
    : center(acenter), radius(aradius) {}

Sphere::Sphere(Point acenter, float aradius, Color acolor)
    : center(acenter), radius(aradius)
{
  color = acolor;
}

Sphere::Sphere(Point acenter, float aradius, char acolor)
    : center(acenter), radius(aradius)
{
  color = colorName(acolor);
}

Color Sphere::get_color(Point point)
{
  return color;
}

Vector Sphere::get_normal(Point p)
{
  Vector v = p - center;
  if (v.norm() == 0)
  {
    return Vector(0.0, 0.0, 0.0);
  }
  return v / v.norm();
}

bool Sphere::on_surface(Point p)
{
  return (radius == (p - center).norm());
}

std::optional<Point> Sphere::intersect(Ray r)
{
  const std::optional<Point> None = std::nullopt;

  Vector direction = r.vec / r.vec.norm();
  Vector oc = r.start - center;

  double a = direction.dot(direction);
  double b = 2.0 * oc.dot(direction);
  double c = oc.dot(oc) - radius * radius;

  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
  {
    return None;
  }

  double sqrt_discriminant = sqrt(discriminant);
  double t1 = (-b - sqrt_discriminant) / (2.0 * a);
  double t2 = (-b + sqrt_discriminant) / (2.0 * a);

  if (t1 > 0)
  {
    Point intersection = r.start + direction * t1;
    return intersection;
  }
  if (t2 > 0)
  {
    Point intersection = r.start + direction * t2;
    return intersection;
  }

  return None;
}
