#pragma once
#include <iostream>

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

typedef struct color_t
{
  int r;
  int g;
  int b;
} color_t;

color_t colorName(char);
color_t mix(color_t, float, color_t, float);
