#include "includes/utils.hpp"
#include <cmath>

Point::Point(float ax, float ay, float az): 
  x(ax), y(ay), z(az) {};

bool Point::operator== (Point other) {
  return (x == other.x && y == other.y && z == other.z);
}

Vector Point::operator-(Point p) {
  return Vector(x - p.x, y - p.y, z - p.z);
}

Point Point::operator+(Vector v) {
  return Point(x + v.x, y + v.y, z + v.z);
}


Vector::Vector(float ax, float ay, float az):
  x(ax), y(ay), z(az) {};

float Vector::norm() {
  return sqrt(x*x + y*y + z*z);
}

float Vector::pt_dot(Point p) {
  return x*p.x + y*p.y + z*p.z;
}

float Vector::dot(Vector v) {
  return x*v.x + y*v.y + z*v.z;
}

Vector Vector::operator+ (Vector v) {
  return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator- (Vector v) {
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator- () {
  return Vector(0.0, 0.0, 0.0) - *this;
}

Vector Vector::operator*(float a) {
  return Vector(a*x, a*y, a*z);
}

Vector Vector::operator/(float a) {
  return (*this*(1/a));
}

Vector Vector::operator*(Vector v){
    return Vector(y * v.z - v.y * z, z *v.x - v.z * x, x *v.y - v.x * y);
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

color_t colorName(char color)
{
  switch (color)
  {
  case 'r': return color_t{255, 0, 0};
  case 'g': return color_t{0, 255, 0};
  case 'b': return color_t{0, 0, 255};
  case 'p': return color_t{255, 0, 255};
  case 'c': return color_t{0, 255, 255};
  case 'y': return color_t{255, 255, 0};
  default:  return color_t{255, 255, 255};
  }
}

color_t mix(color_t c1, float i1, color_t c2, float i2) {
  // Calcul de la couleur résultante par moyenne pondérée
  color_t res = {
    static_cast<int>((c1.r * i1 + c2.r * i2) / (i1 + i2)),
    static_cast<int>((c1.g * i1 + c2.g * i2) / (i1 + i2)),
    static_cast<int>((c1.b * i1 + c2.b * i2) / (i1 + i2)),
  };
  return res;
}
