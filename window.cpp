#include "window.h"
#include "player.h"

void rc::Window::init() {
    // Create a window, centered on both axis, sized by WINDOW_WIDTH, WINDOW_HEIGHT
    _window = SDL_CreateWindow(
            _title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0);

    if (_window == nullptr) {
        std::cerr << "Failed to create window\n";
    }

    // Create a renderer
    _renderer = SDL_CreateRenderer(_window,
                                   -1, SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr) {
        std::cerr << "Failed to create renderer\n";
    }

    _distanceFromProjectionPlane = _raycaster->getDistanceFromProjectionPlane(WINDOW_WIDTH);
}

void rc::Window::release() {
    delete _map;
    delete _player;
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void rc::Window::show() {
    // Game loop
    while (true) {
        pollEvents();
        update();
        draw();
    }
}

void rc::Window::update() {
    _raycaster->castAllRays(_player->_rotationAngle, *_map, _player->_x, _player->_y, WINDOW_WIDTH);
    _player->update(*_map);
}

void rc::Window::draw() {
    // Render background to white
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    SDL_RenderSetScale(_renderer, 1, 1);
    // Render 3D map
    _map->render3D(_renderer, _raycaster->getWallStripHeights(
            _player->_rotationAngle, _distanceFromProjectionPlane));

    SDL_RenderSetScale(_renderer, minimapScale, minimapScale);
    // Render the 2D map
    _map->render(_renderer);

    // Render player
    _player->render(_renderer);

    // Render FOV rays
    for (auto &ray : _raycaster->rays()) {
        ray.render(_renderer, _player->_x, _player->_y);
    }

    // Update screen
    SDL_RenderPresent(_renderer);
}

void rc::Window::HandleKey(SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            release();
            exit(0);
        case SDLK_RIGHT:
            if (event.type == SDL_KEYDOWN) {
                _player->moveRight();
            } else if (event.type == SDL_KEYUP) {
                _player->releaseKey();
            }
            break;
        case SDLK_DOWN:
            if (event.type == SDL_KEYDOWN) {
                _player->moveBackwards();
            } else if (event.type == SDL_KEYUP) {
                _player->releaseKey();
            }
            break;
        case SDLK_UP:
            if (event.type == SDL_KEYDOWN) {
                _player->moveForward();
            } else if (event.type == SDL_KEYUP) {
                _player->releaseKey();
            }
            break;
        case SDLK_LEFT:
            if (event.type == SDL_KEYDOWN) {
                _player->moveLeft();
            } else if (event.type == SDL_KEYUP) {
                _player->releaseKey();
            }
            break;
        case SDLK_w: {
            float plusScale = minimapScale + 0.1f;
            minimapScale = (plusScale > 2.0) ? 2.0f : plusScale;
        }
            break;
        case SDLK_s: {
            float minusScale = minimapScale - 0.1f;
            minimapScale = (minusScale < 0.0) ? 0.0f : minusScale;
        }
            break;
    }
}

void rc::Window::pollEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            release();
            exit(0);
        } else {
            HandleKey(event);
        }
    }
}