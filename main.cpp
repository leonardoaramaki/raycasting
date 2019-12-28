#include <iostream>
#include <SDL2/SDL.h>
#include "window.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed initializing SDL\n";
        return 0;
    } else {
        rc::Window window("Raycasting Demo");
        window.show();
    }
}
