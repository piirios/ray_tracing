#include "utils.hpp"
#include "ray.hpp"
#include <optional>

class Object
{
protected:
    Point origin;

public:
    virtual color_t get_color(float point) = 0;
    virtual Vector get_normal(float point) = 0;
    virtual std::optional<Point> intersect(Ray r) = 0;
};