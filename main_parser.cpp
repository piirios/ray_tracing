#include <iostream>
#include "includes/scene_loader.h"

int main() {
    try {
        Scene scene = loadSceneFromJson("test.json");
        std::cout << "Scène chargée avec succès !" << std::endl;

        // Affiche ou utilise la scène chargée ici
        // Exemple : scene.render();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
