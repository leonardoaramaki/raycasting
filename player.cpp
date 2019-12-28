#include "player.h"
#include "map.h"
#include <cmath>
#include <iostream>

void Player::render(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_Rect rect{
            _x,
            _y,
            (int) _radius,
            (int) _radius
    };
    SDL_RenderFillRect(renderer, &rect);
    int x = _x - _radius / 2;
    int y = _y - _radius / 2;
    SDL_RenderDrawLine(renderer,
                       x,
                       y,
                       x + cos(_rotationAngle) * _radius,
                       y + sin(_rotationAngle) * _radius);
}

void Player::update(const rc::Map &map) {
    _rotationAngle += _turnDirection * _rotationSpeed;

    auto moveStep = _walkDirection * _moveSpeed;
    auto nextPlayerX = _x + cos(_rotationAngle) * moveStep;
    auto nextPlayerY = _y + sin(_rotationAngle) * moveStep;

    bool facingForward = sin(_rotationAngle) >= 0;
    bool facingRight = cos(_rotationAngle) >= 0;
    unsigned playerVertSpacing = (facingForward) ? _radius : 0;
    unsigned playerHorizSpacing = (facingRight) ? _radius : 0;
    if (!map.isWallAt(nextPlayerX + playerHorizSpacing, nextPlayerY + playerVertSpacing)) {
        _x = nextPlayerX;
        _y = nextPlayerY;
    }
}

void Player::moveRight() {
    _turnDirection = +1;
}

void Player::moveForward() {
    _walkDirection = +1;
}

void Player::moveBackwards() {
    _walkDirection = -1;
}

void Player::moveLeft() {
    _turnDirection = -1;
}

void Player::releaseKey() {
    _walkDirection = 0;
    _turnDirection = 0;
}
