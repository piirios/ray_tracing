#include <SFML/Graphics.hpp>
#include "ppm_loader.hpp"

int main() {
    std::string filename = "test2.ppm";  // Le nom du fichier PPM à charger
    PPMImage image = loadPPM(filename);

    if (image.pixels.empty()) {
        return -1;
    }

    // Crée une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "PPM Viewer");

    // Crée une texture SFML et un sprite pour afficher l'image
    sf::Texture texture;
    texture.create(image.width, image.height);
    texture.update(reinterpret_cast<const sf::Uint8*>(image.pixels.data()));
    sf::Sprite sprite(texture);

    // Affichage de l'image dans la fenêtre
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);  // Dessiner l'image
        window.display();
    }

    return 0;
}

//  g++ -o ppm_viewer main.cpp ppm_loader.cpp -lsfml-graphics -lsfml-window -lsfml-system
//  ./ppm_viewer

