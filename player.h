#ifndef RAYCASTING_PLAYER_H
#define RAYCASTING_PLAYER_H

#include <cmath>
#include <SDL.h>
#include "map.h"
#include "raycasting.h"

class Player {
public:
    const static unsigned _radius = 8.0f;
public:
    int _x = 0;
    int _y = 0;
    int _turnDirection = 0;
    int _walkDirection = 0;
    float _rotationAngle = M_PI / 2.0f;
    float _rotationSpeed = 2 * M_PI / 180;
    float _moveSpeed = 2.0f;

public:
    Player(int x, int y) : _x(x), _y(y) {
    }

public:
    void update(const rc::Map &map);

    void render(SDL_Renderer* renderer) const;

    void moveRight();

    void moveLeft();

    void moveBackwards();

    void moveForward();

    void releaseKey();
};


#endif //RAYCASTING_PLAYER_H
