#include "includes/scene.hpp"
#include "includes/json.hpp"
#include "includes/sphere.hpp"
#include <MiniFB_cpp.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

Scene::Scene(double ratio, int width) : sky(Sky(colorName('b')))
{
    camera = Camera(Point(), Vector::get_ez(), 1.0, width, ratio, 2.0);
    pixel.reserve(camera.width * camera.height);
};

Scene::Scene(const std::string &file_path, double ratio, int width)
    : camera(Point(0, 0, 0), Vector(0, 0, 1), 1.0, width, ratio, 2.0), sky(Sky(colorName('b')))
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + file_path);
    }

    json scene_data;
    file >> scene_data;

    // Charger la caméra
    json camera_data = scene_data["camera"];
    Point position(
        camera_data["position"][0],
        camera_data["position"][1],
        camera_data["position"][2]);
    Vector direction(
        camera_data["direction"][0],
        camera_data["direction"][1],
        camera_data["direction"][2]);
    double distance = camera_data["distance"];
    double viewport_width = camera_data["viewport_width"];

    this->camera = Camera(position, direction, distance, width, ratio, viewport_width);

    // Charger les objets
    for (const auto &obj : scene_data["objects"])
    {
        if (obj["type"] == "sphere")
        {
            Sphere sphere(
                Point(obj["position"][0], obj["position"][1], obj["position"][2]),
                obj["radius"],
                Color(obj["color"][0], obj["color"][1], obj["color"][2]));
            this->obj_list.push_back(sphere);
        }
        else
        {
            std::cerr << "Type d'objet non pris en charge : " << obj["type"] << std::endl;
        }
    }
}

int Scene::height() const
{
    return camera.height;
}

int Scene::width() const
{
    return camera.width;
}

void Scene::render()
{
    pixel.reserve(camera.width * camera.height);
    for (int i = 0; i < camera.width; i++)
    {
        for (int j = 0; j < camera.height; j++)
        {
            Object *obj_hit = &sky;
            std::optional<float> dist = std::nullopt; // use null opt as infty dist
            std::optional<Point> p = std::nullopt;
            Ray ray = camera.build_ray(i, j);
            for (std::vector<Object>::iterator obj = obj_list.begin(); obj < obj_list.end(); obj++)
            {
                p = (*obj).intersect(ray); // try to intersect objet
                if (p.has_value())
                {
                    float new_dist = (*p - ray.start).norm();  // UNSAFE: here p is not null (otherwise we will be outside of this bloc)
                    if (!dist.has_value() || *dist > new_dist) // UNSAFE: here dist is not null (otherwise we will match the fist cond)
                    {
                        obj_hit = &(*obj);
                        dist = new_dist;
                    }
                }
            }
            if (!p.has_value())
            {
                p = (*obj_hit).intersect(ray);
            }
            // invariant: p isn't null
            pixel[i + j * camera.height] = (*obj_hit).get_color(*p).into();
        }
    }
}

void Scene::display()
{
    int WIDTH = this->width();
    int HEIGHT = this->height();

    // Créer une fenêtre avec MiniFB
    struct mfb_window *window = mfb_open("MiniFB Scene Display", WIDTH, HEIGHT);
    if (!window)
    {
        std::cerr << "Erreur : impossible de créer la fenêtre.\n";
        return;
    }

    // Boucle principale pour afficher les pixels
    while (mfb_wait_sync(window))
    {
        // Mettre à jour l'affichage avec le vecteur de pixels
        if (mfb_update(window, pixel.data()) < 0)
        {
            break; // Quitter si l'utilisateur ferme la fenêtre
        }
    }
}