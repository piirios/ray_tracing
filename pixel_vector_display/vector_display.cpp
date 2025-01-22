#include "minifb/include/MiniFB.h"
 // Inclure MiniFB
#include <vector>   // Pour std::vector
#include <iostream> // Pour std::cerr en cas d'erreur

// Définir le type de couleur (ARGB)
typedef uint32_t color_t;

// Dimensions de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    // Créer une fenêtre avec MiniFB
    struct mfb_window *window = mfb_open("MiniFB Pixel Display", WIDTH, HEIGHT);
    if (!window) {
        std::cerr << "Erreur : impossible de créer la fenêtre.\n";
        return -1;
    }

    // Créer un vecteur de pixels
    std::vector<color_t> pixels(WIDTH * HEIGHT);

    // Remplir le vecteur avec des couleurs (par exemple, un dégradé)
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            color_t red   = (x * 255) / WIDTH;
            color_t green = (y * 255) / HEIGHT;
            color_t blue  = 128; // Une valeur constante pour le bleu
            pixels[y * WIDTH + x] = (red << 16) | (green << 8) | blue; // ARGB
        }
    }

    // Boucle principale pour afficher les pixels
    while (mfb_wait_sync(window)) {
        // Afficher les pixels à l'écran
        if (mfb_update(window, pixels.data()) < 0) {
            break; // Quitter si l'utilisateur ferme la fenêtre
        }
    }

    return 0;
}

// g++ -std=c++17 -o pixel_display vector_display.cpp -L/home/glegros66/STIC/vector_visu/minifb/build -L/usr/lib/x86_64-linux-gnu -lminifb -lX11 -lXrandr -lXinerama -lXcursor -lGL -lm -ldl -Wl,-rpath,/usr/lib/x86_64-linux-gnu

// ./pixel_display


