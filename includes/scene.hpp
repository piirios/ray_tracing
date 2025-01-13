#include "object.hpp"
#include "camera.hpp"
#include "utils.hpp"
#include <vector>

class Scene
{
private:
    Camera camera;
    int width;
    int heigth;

public:
    Scene(double ratio, int width);

    // TODO: implémenter une structure plus puissante (équivalent d'arbre kdim ?)
    std::vector<Object> obj_list; // liste des objets

    std::vector<color_t> pixel; // rendu de la scene

    double inline ratio() const; // permet de récupérer le ratio
};