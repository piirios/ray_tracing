#include "utils.hpp"
#include "ray.hpp"
#include <optional>

class Object
{
protected:
    Point origin;

public:
    virtual color_t get_color(Point point) = 0;
    virtual Vector get_normal(Point point) = 0;
    virtual std::optional<Point> intersect(Ray r) = 0;
};