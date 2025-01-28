#include "includes/utils.hpp"
#include <cmath>
#include <random>

inline double random_double()
{
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

Point::Point(float ax, float ay, float az) : x(ax), y(ay), z(az) {};

Point::Point() : x(0.), y(0.), z(0.) {};

bool Point::operator==(Point other)
{
  return (x == other.x && y == other.y && z == other.z);
}

Vector Point::operator-(Point p)
{
  return Vector(x - p.x, y - p.y, z - p.z);
}

Point Point::operator+(Vector v)
{
  return Point(x + v.x, y + v.y, z + v.z);
}

Point Point::operator-(Vector v)
{
  return Point(x - v.x, y - v.y, z - v.z);
}

Vector::Vector() : x(.0), y(.0), z(.0) {};
Vector::Vector(float ax, float ay, float az) : x(ax), y(ay), z(az) {};

Vector Vector::random_unit()
{
  while (true)
  {
    auto v = Vector(-1. + 2 * random_double(), -1. + 2 * random_double(), -1. + 2 * random_double());
    auto norm = v.norm();
    if (1e-60 < norm)
    {
      return v / v.norm();
    }
  }
}

float Vector::norm()
{
  return sqrt(x * x + y * y + z * z);
}

float Vector::pt_dot(Point p)
{
  return x * p.x + y * p.y + z * p.z;
}

float Vector::dot(Vector v)
{
  return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator+(Vector v)
{
  return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v)
{
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator-()
{
  return Vector(0.0, 0.0, 0.0) - *this;
}

Vector Vector::operator*(float a)
{
  return Vector(a * x, a * y, a * z);
}

Vector Vector::operator/(float a)
{
  return (*this * (1 / a));
}

Vector Vector::operator*(Vector v)
{
  return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

Vector Vector::operator*(double t)
{
  return Vector(t * x, t * y, t * z);
}

std::ostream &
operator<<(std::ostream &stream, const Vector &v)
{
  stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return stream;
}

std::ostream &
operator<<(std::ostream &stream, const Point &p)
{
  stream << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return stream;
}

Vector Vector::get_ex()
{
  return Vector(1.0, 0.0, 0.0);
}

Vector Vector::get_ey()
{
  return Vector(0.0, 1.0, 0.0);
}

Vector Vector::get_ez()
{
  return Vector(0.0, 0.0, 1.0);
}

Color colorName(char color)
{
  switch (color)
  {
  case 'r':
    return Color{255, 0, 0};
  case 'g':
    return Color{0, 255, 0};
  case 'b':
    return Color{0, 0, 255};
  case 'p':
    return Color{255, 0, 255};
  case 'c':
    return Color{0, 255, 255};
  case 'y':
    return Color{255, 255, 0};
  default:
    return Color{255, 255, 255};
  }
}

Color mix(Color c1, float i1, Color c2, float i2)
{
  // Calcul de la couleur résultante par moyenne pondérée
  Color res = {
      static_cast<int>((c1.r * i1 + c2.r * i2) / (i1 + i2)),
      static_cast<int>((c1.g * i1 + c2.g * i2) / (i1 + i2)),
      static_cast<int>((c1.b * i1 + c2.b * i2) / (i1 + i2)),
  };
  return res;
}

std::pair<double, double> sample_square()
{
  // Create a random number generator
  static std::random_device rd;                           // Seed
  static std::mt19937 gen(rd());                          // Random number generator
  static std::uniform_real_distribution<> dis(-0.5, 0.5); // Uniform distribution in [-0.5, 0.5]

  // Generate random offsets within the unit square
  double x = dis(gen);
  double y = dis(gen);

  return {x, y};
}
