#include "includes/object.hpp"
#include "includes/utils.hpp"
#include "includes/scene.hpp"
#include "includes/sphere.hpp"
#include "includes/ground.hpp"
#include <fstream>
#include <vector>
#include <string>

void write_ppm(const std::string &filename, int image_width, int image_height, const std::vector<Color> &pixels)
{
    // Ouvre un fichier en écriture
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    if (!out)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    // Écrit l'en-tête PPM
    out << "P3\n"
        << image_width << " " << image_height << "\n255\n";

    // Parcourt chaque pixel et écrit les valeurs RGB
    for (int j = 0; j < image_height; ++j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            const auto &color = pixels[i + j * image_width];

            // Écrit les valeurs RGB dans le fichier
            out << color.r << " " << color.g << " " << color.b << "\n";
        }
    }

    // Ferme le fichier
    out.close();
}

int main(void)
{

    Scene scene = Scene("test.json", 16.0 / 9.0, 800);
    scene.render();
    std::cout << "render done" << std::endl;
    scene.display();
    // write_ppm("test.ppm", scene.width(), scene.height(), res);

    return 0;
}