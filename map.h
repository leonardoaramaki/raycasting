#ifndef RAYCASTING_MAP_H
#define RAYCASTING_MAP_H

#include <vector>
#include <SDL_render.h>

namespace rc {
    struct MapConstants {
        const static unsigned MAP_NUM_COLS = 10;
        const static unsigned MAP_NUM_ROWS = 7;
        const static unsigned TILE_SIZE = 32;
    };

    class Map {
    private:
        const int _grid[MapConstants::MAP_NUM_ROWS][MapConstants::MAP_NUM_COLS] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

    public:
        void render(SDL_Renderer *renderer) const;

        void render3D(SDL_Renderer* renderer, const std::vector<unsigned>& wallStripeHeights) const;

        bool isWallAt(unsigned x, unsigned y) const;
    };
}

#endif //RAYCASTING_MAP_H
