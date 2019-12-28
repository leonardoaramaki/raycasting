#include "ray.h"
#include "map.h"
#include "player.h"
#include "window.h"
#include <iostream>

#define LOG(X) std::cout << X << std::endl;

namespace rc {
    enum Color {
        BLACK,
        BLUE,
        RED
    };
};

void rc::Ray::checkVerticalIntersects(const Map &map) {
    long intersectX, intersectY;

    bool isRayCastingRight = cos(_angleInRadians) >= 0;
    bool isRayCastingDown = sin(_angleInRadians) >= 0;
    float stepx, stepy;

    _verticalIntersectionPoints.clear();

    // Coordinates on map grid
    float gridX = floor(_originX / MapConstants::TILE_SIZE);

    // Ray is being cast to the right, the y-intersection point should be at the nearest-right position of the viewer
    if (isRayCastingRight) {
        intersectX = (gridX + 1) * MapConstants::TILE_SIZE + 1;
    } else {
        // Ray is being cast to the left, the y-intersection point should be at the nearest-left position of the viewer
        intersectX = gridX * MapConstants::TILE_SIZE - 1;
    }

    intersectY = _originY + tan(_angleInRadians) * (intersectX - _originX);

    stepx = MapConstants::TILE_SIZE;
    stepx *= isRayCastingRight ? 1 : -1;
    stepy = stepx * tan(_angleInRadians);
    stepy *= (!isRayCastingDown && stepy > 0) ? -1 : 1;
    stepy *= (isRayCastingDown && stepy < 0) ? -1 : 1;

    while (intersectX > 0 && intersectX < Window::WINDOW_WIDTH
           && intersectY > 0 && intersectY < Window::WINDOW_HEIGHT) {

        if (map.isWallAt(intersectX, intersectY)) {
            _distance = sqrt(abs(intersectX - _originX) * abs(intersectX - _originX) +
                             abs(intersectY - _originY) * abs(intersectY - _originY));

            _collisionPoints.push_back(CollisionPoint{intersectX, intersectY});
            break;
        } else {
            _verticalIntersectionPoints.push_back(IntersectionPoint{intersectX, intersectY});
        }

        intersectX += stepx;
        intersectY += stepy;
    }
}

void rc::Ray::checkHorizontalIntersects(const Map &map) {
    int intersectX, intersectY;

    bool isRayCastingRight = cos(_angleInRadians) >= 0;
    bool isRayCastingDown = sin(_angleInRadians) >= 0;
    float stepx, stepy;

    _horizontalIntersectionPoints.clear();

    // Coordinates on map grid
    float gridY = floor(_originY / MapConstants::TILE_SIZE);

    if (isRayCastingDown) {
        intersectY = (gridY + 1) * MapConstants::TILE_SIZE + 1;
    } else {
        intersectY = gridY * MapConstants::TILE_SIZE - 1;
    }

    intersectX = _originX + (intersectY - _originY) / tan(_angleInRadians);

    stepy = MapConstants::TILE_SIZE;
    stepy *= isRayCastingDown ? 1 : -1;
    stepx = stepy / tan(_angleInRadians);
    stepx *= (!isRayCastingRight && stepx > 0) ? -1 : 1;
    stepx *= (isRayCastingRight && stepx < 0) ? -1 : 1;

    while (intersectX > 0 && intersectX < Window::WINDOW_WIDTH
           && intersectY > 0 && intersectY < Window::WINDOW_HEIGHT) {
        if (map.isWallAt(intersectX, intersectY)) {
            _distance = sqrt(abs(intersectX - _originX) * abs(intersectX - _originX) +
                             abs(intersectY - _originY) * abs(intersectY - _originY));
            _collisionPoints.push_back(CollisionPoint{intersectX, intersectY});
            break;
        } else {
            _horizontalIntersectionPoints.push_back(IntersectionPoint{intersectX, intersectY});
        }

        intersectX += stepx;
        intersectY += stepy;
    }
}

static int distanceFromPoint(int x, int y, int pX, int pY) {
    return sqrt(abs(x - pX) * abs(x - pX) +
                abs(y - pY) * abs(y - pY));
}

bool rc::Ray::cast(const Map &map) {
    checkHorizontalIntersects(map);
    checkVerticalIntersects(map);

    CollisionPoint closerPoint = _collisionPoints.front();

    for (auto &point : _collisionPoints) {
        int closestDistance = distanceFromPoint(closerPoint.x, closerPoint.y, _originX, _originY);
        if (distanceFromPoint(point.x, point.y, _originX, _originY) < closestDistance) {
            closerPoint = point;
        }
    }

    // Minimum distance from walls should be at least the player's size.
    _distance = std::max(static_cast<int>(distanceFromPoint(closerPoint.x, closerPoint.y, _originX, _originY)),
                         static_cast<int>(Player::_radius));

    _collisionPoints.clear();
    _collisionPoints.push_back(closerPoint);

    return false;
}

static void
drawPoints(SDL_Renderer *renderer, const std::vector<rc::Point> &points, rc::Color color) {
    for (auto &intersection : points) {
        // Collision points are drawn red
        switch (color) {
            case rc::BLACK:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                break;
            case rc::BLUE:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            case rc::RED:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
        }
        SDL_Rect rect{intersection.x, intersection.y, 5, 5};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void rc::Ray::render(SDL_Renderer *renderer, unsigned originX, unsigned originY) const {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
                       originX,
                       originY,
                       originX + cos(_angleInRadians) * _distance,
                       originY + sin(_angleInRadians) * _distance);


    if (_drawHorizIntersectionPoints) {
        drawPoints(renderer, _horizontalIntersectionPoints, Color::BLUE);
    }

    if (_drawVertIntersectionPoints) {
        drawPoints(renderer, _verticalIntersectionPoints, Color::BLACK);
    }

    if (_drawCollisionPoints) {
        drawPoints(renderer, _collisionPoints, Color::RED);
    }
}

void rc::Ray::setDistance(int newDistance) {
    _distance = newDistance;
}


