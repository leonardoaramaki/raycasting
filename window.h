#ifndef RAYCASTING_WINDOW_H
#define RAYCASTING_WINDOW_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "map.h"
#include "player.h"

namespace rc {
    class Window {
    public:
        static const int WINDOW_WIDTH = 640;
        static const int WINDOW_HEIGHT = 420;

    private:
        std::string _title;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        rc::Map *_map = new Map();
        Player *_player = new Player(
                MapConstants::MAP_NUM_COLS / 2 * MapConstants::TILE_SIZE,
                MapConstants::MAP_NUM_ROWS / 2 * MapConstants::TILE_SIZE
        );
        rc::Raycaster *_raycaster = new Raycaster(60);
        float _distanceFromProjectionPlane = 0;
        float minimapScale = 0.6f;

    private:
        void init();

        /**
         * Destroy any allocated resources.
         */
        void release();

        void HandleKey(SDL_Event &event);

        void pollEvents();

        void update();

        void draw();

    public:
        explicit Window(const char *title) : _title(title) {
            init();
        };

        explicit Window(std::string &title) : _title(title) {
            init();
        };

        ~Window() {
            release();
        };

    public:

        /**
         * Show Window by start listening to incoming Events.
         */
        void show();
    };
}

#endif //RAYCASTING_WINDOW_H
