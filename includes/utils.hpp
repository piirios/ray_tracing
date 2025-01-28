#pragma once
#include <iostream>
#include <cstdlib>

class Vector;
class Point;

class Point
{
public:
  float x;
  float y;
  float z;

  Point(float, float, float);
  Point();
  Point operator-(Vector);
  Vector operator-(Point);
  bool operator==(Point);
  Point operator+(Vector);
};

class Vector
{
public:
  float x;
  float y;
  float z;

  Vector();
  Vector(float, float, float);
  float norm();
  float pt_dot(Point);
  float dot(Vector); // produit scalaire
  Vector operator-();
  Vector operator+(Vector);
  Vector operator-(Vector);
  Vector operator*(float);
  Vector operator/(float);
  Vector operator*(Vector); // produit vectoriel
  Vector operator*(double); // multiplication scalaire
  friend std::ostream &operator<<(std::ostream &, const Vector &);

  // const
  static Vector get_ex();
  static Vector get_ey();
  static Vector get_ez();
};

class Color
{
public:
  int r;
  int g;
  int b;

  Color() : r(0), g(0), b(0) {};
  Color(int a, int b, int c) : r(a), g(b), b(c) {};

  uint32_t into()
  {
    return (r << 16) | (g << 8) | b;
  };
};

Color colorName(char);
Color mix(Color, float, Color, float);

std::pair<double, double> sample_square();