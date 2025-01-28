#include "includes/scene.hpp"
#include "includes/json.hpp"
#include "includes/ground.hpp"
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
    : camera(Point(0, 0, 0), Vector(0, 0, 1), 1.0, width, ratio, 2.0), sky(Sky(colorName('g')))
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

    std::cout << "Position de la caméra : (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    std::cout << "Direction de la caméra : (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
    std::cout << "Distance : " << distance << ", Largeur du viewport : " << viewport_width << std::endl;
    // Charger les objets
    for (const auto &obj : scene_data["objects"])
    {
        if (obj["type"] == "sphere")
        {
            Sphere *sphere = new Sphere(
                Point(obj["position"][0], obj["position"][1], obj["position"][2]),
                obj["radius"],
                Color(obj["color"][0], obj["color"][1], obj["color"][2]));
            this->obj_list.push_back(sphere);

            std::cout << "  Sphère : Position = (" << obj["position"][0] << ", " << obj["position"][1] << ", " << obj["position"][2]
                      << "), Rayon = " << obj["radius"]
                      << ", Couleur = (" << obj["color"][0] << ", " << obj["color"][1] << ", " << obj["color"][2] << ")" << std::endl;
        }
        else if (obj["type"] == "ground")
        {
            Ground *ground = new Ground(
                Color(obj["color"][0], obj["color"][1], obj["color"][2]));
            this->obj_list.push_back(ground);

            std::cout << "  Ground : Hauteur = " << obj["height"]
                      << ", Couleur = (" << obj["color"][0] << ", " << obj["color"][1] << ", " << obj["color"][2] << ")" << std::endl;
        }
        else
        {
            std::cerr << "Type d'objet non pris en charge : " << obj["type"] << std::endl;
        }
    }
}

Scene::~Scene()
{
    for (auto obj : obj_list)
    {
        delete obj;
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
    pixel.resize(camera.width * camera.height);

    std::cout << "Nombre d'objets dans la scène : " << obj_list.size() << std::endl;
    for (int i = 0; i < camera.width; i++)
    {
        for (int j = 0; j < camera.height; j++)
        {
            Ray ray = camera.build_ray(i, j);
            Object *closest_object = nullptr;
            Point closest_intersection;
            float closest_distance = std::numeric_limits<float>::max();
            for (auto &obj : obj_list)
            {
                auto intersection = obj->intersect(ray);
                if (intersection.has_value())
                {
                    float distance = (intersection.value() - ray.start).norm();

                    if (distance < closest_distance)
                    {
                        closest_distance = distance;
                        closest_object = obj;
                        closest_intersection = intersection.value();
                    }
                }
                else
                {
                }
            }

            if (closest_object)
            {
                pixel[i + j * camera.width] = closest_object->get_color(closest_intersection).into();
            }
            else
            {
                pixel[i + j * camera.width] = sky.get_color(Point()).into();
            }
        }
    }
}

void Scene::display()
{
    int WIDTH = this->width();
    int HEIGHT = this->height();

    struct mfb_window *window = mfb_open("MiniFB Scene Display", WIDTH, HEIGHT);
    if (!window)
    {
        std::cerr << "Erreur : impossible de créer la fenêtre.\n";
        return;
    }

    while (mfb_wait_sync(window))
    {

        if (mfb_update(window, pixel.data()) < 0)
        {
            break;
        }
    }
}