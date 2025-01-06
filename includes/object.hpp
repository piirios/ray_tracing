#include <optional>

class Object
{
    virtual std::optional<float> intersect(float r) { return std::optional<float>(); };
};