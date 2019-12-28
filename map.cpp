#include "map.h"
#include "window.h"

/**
 * Render the 2D map of the scene.
 * @param renderer
 */
void rc::Map::render(SDL_Renderer *renderer) const {
    for (auto i = 0; i < MapConstants::MAP_NUM_ROWS; i++) {
        for (auto j = 0; j < MapConstants::MAP_NUM_COLS; j++) {
            int tileX = j * MapConstants::TILE_SIZE;
            int tileY = i * MapConstants::TILE_SIZE;

            SDL_Rect rect{
                    tileX, tileY,
                    static_cast<int>(MapConstants::TILE_SIZE),
                    static_cast<int>(MapConstants::TILE_SIZE)
            };

            if (_grid[i][j] == 1) {
                // Brown color for walls
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else {
                // Draw borders to each grid cell
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

/**
 * Render the 3D projection of the 2D map.
 * @param renderer
 * @param wallStripeHeights
 */
void rc::Map::render3D(SDL_Renderer *renderer, const std::vector<unsigned> &wallStripeHeights) const {
    for (int i = 0; i < wallStripeHeights.size(); i++) {
        auto stripHeight = static_cast<int>(wallStripeHeights[i]);
        auto stripeHue = stripHeight;

        if (stripeHue > 255) {
            stripeHue = 255;
        }

        // Simulate shadow by setting darker colors along with distance.
        SDL_SetRenderDrawColor(renderer, 0, 0, stripeHue, 255);
        SDL_Rect rect{i, Window::WINDOW_HEIGHT / 2 - stripHeight / 2, 2, stripHeight};
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool rc::Map::isWallAt(unsigned x, unsigned y) const {
    if (x < 0 || x > MapConstants::MAP_NUM_COLS * MapConstants::TILE_SIZE || y < 0 ||
        y > MapConstants::MAP_NUM_ROWS * MapConstants::TILE_SIZE) {
        return true;
    }

    int gridX = x / MapConstants::TILE_SIZE;
    int gridY = y / MapConstants::TILE_SIZE;

    return _grid[gridY][gridX] != 0;
}