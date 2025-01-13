#ifndef PPM_LOADER_HPP
#define PPM_LOADER_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct PPMImage {
    int width;
    int height;
    std::vector<sf::Color> pixels;
};

PPMImage loadPPM(const std::string& filename);

#endif // PPM_LOADER_HPP

