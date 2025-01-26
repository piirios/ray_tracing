#include <iostream>
#include <fstream>
#include "includes/json.hpp"
#include "includes/scene.hpp"
#include "includes/camera.hpp"
#include "includes/sphere.hpp"
#include "includes/utils.hpp"

using json = nlohmann::json;

// Fonction pour charger une scène depuis un fichier JSON
Scene loadSceneFromJson(const std::string& file_path, double ratio, int width) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + file_path);
    }

    json scene_data;
    file >> scene_data;

    // Charger la caméra
    json camera_data = scene_data["camera"];
    Point position(
        camera_data["position"][0], 
        camera_data["position"][1], 
        camera_data["position"][2]
    );
    Vector direction(
        camera_data["direction"][0], 
        camera_data["direction"][1], 
        camera_data["direction"][2]
    );
    double distance = camera_data["distance"];
    double viewport_width = camera_data["viewport_width"];

    Camera camera(position, direction, distance, width, ratio, viewport_width);

    // Créer la scène avec la caméra
    Scene scene(ratio, width);
    scene.camera = camera;

    // Charger les objets
    for (const auto& obj : scene_data["objects"]) {
        if (obj["type"] == "sphere") {
            Sphere sphere(
                Point(obj["position"][0], obj["position"][1], obj["position"][2]),
                obj["radius"],
                color_t(obj["color"][0], obj["color"][1], obj["color"][2]),
                obj["reflective"]
            );
            scene.obj_list.push_back(sphere);
        } else {
            std::cerr << "Type d'objet non pris en charge : " << obj["type"] << std::endl;
        }
    }

    // Charger les lumières (à implémenter si nécessaire dans votre structure)
    for (const auto& light : scene_data["lights"]) {
        if (light["type"] == "point") {
            // Implémentation à ajouter en fonction de votre classe PointLight ou similaire
            std::cerr << "Chargement des lumières non implémenté." << std::endl;
        }
    }

    return scene;
}
