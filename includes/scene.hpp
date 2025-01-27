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

public:
    Camera camera;

    // TODO: implémenter une structure plus puissante (équivalent d'arbre kdim ?)
    std::vector<Object> obj_list; // liste des objets

    std::vector<uint32_t> pixel; // rendu de la scene

    Scene(double ratio, int width);
    Scene(const std::string &file_path, double ratio, int width);

    // double inline ratio() const; // permet de récupérer le ratio
    int height() const;
    int width() const;

    void render();
    void display();
};