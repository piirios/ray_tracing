#include "includes/scene.hpp"

Scene::Scene(double ratio, int width)
{
    camera = Camera(Point(), Vector::get_ez(), 1.0, width, ratio, 2.0);
}
