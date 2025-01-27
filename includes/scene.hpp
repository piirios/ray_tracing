#pragma once
#include "object.hpp"
#include "camera.hpp"
#include "utils.hpp"
#include "sky.hpp"
#include <vector>

class Scene
{
private:
    Sky sky; // default objet to intersect
    int samples_per_pixel;
    int max_depth;

public:
    Camera camera;

    // TODO: implémenter une structure plus puissante (équivalent d'arbre kdim ?)
    std::vector<Object *> obj_list; // liste des objets

    std::vector<uint32_t> pixel; // rendu de la scene

    Scene(double ratio, int width);
    Scene(const std::string &file_path, double ratio, int width);
    ~Scene();

    // double inline ratio() const; // permet de récupérer le ratio
    int height() const;
    int width() const;

    void render();

    std::optional<std::pair<Object *, Point>> try_hit(Ray r);

    Color ray_color(Ray r, int depth);

    void display();
};