#include "utils.hpp"
#include <optional>

class Object
{
protected:
    Point origin;

public:
    virtual float get_color(float point) = 0;
    virtual float get_normal(float point) = 0;
    virtual std::optional<float> intersect(float r) = 0;
};