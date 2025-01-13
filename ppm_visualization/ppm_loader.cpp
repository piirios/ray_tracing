#include "ppm_loader.hpp"
#include <fstream>
#include <iostream>

PPMImage loadPPM(const std::string& filename) {
    PPMImage image;
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier " << filename << std::endl;
        return image;
    }

    std::string header;
    file >> header;
    if (header != "P6") {
        std::cerr << "Format PPM invalide. Attendu P6." << std::endl;
        return image;
    }

    file >> image.width >> image.height;
    int maxColor;
    file >> maxColor;
    file.ignore(); // Ignore le caractère de nouvelle ligne après la tête du fichier PPM

    image.pixels.resize(image.width * image.height);

    for (int i = 0; i < image.width * image.height; ++i) {
        uint8_t r, g, b;
        file.read(reinterpret_cast<char*>(&r), 1);
        file.read(reinterpret_cast<char*>(&g), 1);
        file.read(reinterpret_cast<char*>(&b), 1);
        image.pixels[i] = sf::Color(r, g, b);
    }

    return image;
}
