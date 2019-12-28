#include <iostream>
#include "raycasting.h"
#include "ray.h"

#define LOG(msg) std::cout << msg << std::endl;

static float normalizeAngle(float angle) {
    float normAngle = fmod(angle, 2 * M_PI);
    if (normAngle < 0) {
        normAngle = 2 * M_PI + normAngle;
    }
    return normAngle;
}

void
rc::Raycaster::castAllRays(float playerRotationAngle, const Map &map, unsigned playerX, unsigned playerY, unsigned numberOfRays) {
    _rays.clear();
    auto rayAngle = playerRotationAngle - (_fovAngle->angleInRadians() / 2);
    for (int i = 0; i < numberOfRays; i++) {
        auto ray = Ray(normalizeAngle(rayAngle), playerX, playerY);
        ray.cast(map);
        _rays.push_back(ray);

        rayAngle += _fovAngle->angleInRadians() / numberOfRays;
    }
}

float rc::Raycaster::getDistanceFromProjectionPlane(size_t screenWidth) const {
    return cos(_fovAngle->angleInRadians() / 2) * screenWidth / 2;
}

const std::vector<unsigned int> &rc::Raycaster::getWallStripHeights(
        const float playerRotationAngle,
        const unsigned distanceProjPlane
) {
    auto *stripHeights = new std::vector<unsigned int>();
    for (auto &ray : _rays) {
        float correctedDistance = cos(ray.angleInRadians() - playerRotationAngle) * ray.distance();
        auto wallStripHeight = (MapConstants::TILE_SIZE / correctedDistance) * distanceProjPlane;
        stripHeights->push_back(wallStripHeight);
    }

    return *stripHeights;
}
