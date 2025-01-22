#include "minifb/include/MiniFB.h"
#include <vector>   // Pour std::vector
#include <iostream> // Pour std::cerr en cas d'erreur
#include <cmath>    // Pour std::sqrt()

// Définir le type de couleur (ARGB)
typedef uint32_t color_t;

// Dimensions de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    // Créer une fenêtre avec MiniFB
    struct mfb_window *window = mfb_open("Dégradé en Cercle", WIDTH, HEIGHT);
    if (!window) {
        std::cerr << "Erreur : impossible de créer la fenêtre.\n";
        return -1;
    }

    // Créer un vecteur de pixels
    std::vector<color_t> pixels(WIDTH * HEIGHT);

    // Coordonnées du centre du cercle
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    // Remplir le vecteur de pixels avec un dégradé de couleurs en forme de cercle
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Calculer la distance du pixel par rapport au centre
            int dx = x - centerX;
            int dy = y - centerY;
            int distance = std::sqrt(dx * dx + dy * dy);

            // Normaliser la distance pour la couleur
            int maxDistance = std::sqrt(centerX * centerX + centerY * centerY); // Distance maximale du centre
            int red   = (distance * 255) / maxDistance; // Rouge augmente avec la distance
            int blue  = 255 - red; // Bleu diminue avec la distance

            // Créer la couleur ARGB (ici, alpha = 255, donc opaque)
            pixels[y * WIDTH + x] = (red << 16) | (0 << 8) | blue; // ARGB
        }
    }

    // Boucle principale pour afficher les pixels
    while (mfb_wait_sync(window)) {
        // Afficher les pixels à l'écran
        if (mfb_update(window, pixels.data()) < 0) {
            break; // Quitter si l'utilisateur ferme la fenêtre
        }
    }

    // Fermer la fenêtre à la fin
    mfb_close(window);

    return 0;
}


// g++ -std=c++17 -o pixel_display vector_cercle.cpp -L/home/glegros66/STIC/vector_visu/minifb/build -L/usr/lib/x86_64-linux-gnu -lminifb -lX11 -lXrandr -lXinerama -lXcursor -lGL -lm -ldl -Wl,-rpath,/usr/lib/x86_64-linux-gnu