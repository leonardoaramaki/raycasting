#ifndef RAYCASTING_RAYCASTING_H
#define RAYCASTING_RAYCASTING_H

#include <cmath>
#include <vector>
#include "ray.h"

namespace rc {

    class FieldOfView {
    private:
        // Angle in degrees
        float _degrees;

    public:
        explicit FieldOfView(float degrees) : _degrees(degrees) {}

        float angleInRadians() const {
            return _degrees * (M_PI / 180);
        }

        float angleInDegrees() const {
            return _degrees;
        }
    };

    /**
     * Responsible for casting and tracing rays.
     */
    class Raycaster {
    private:
        rc::FieldOfView *_fovAngle;
        std::vector<Ray> _rays;

    public:
        explicit Raycaster(float fovAngle) {
            _fovAngle = new FieldOfView(fovAngle);
        }

        ~Raycaster() {
            delete _fovAngle;
        }

    public:
        std::vector<Ray> rays() const {
            return _rays;
        };

        void castAllRays(float playerRotationAngle, const Map &map, unsigned playerX, unsigned playerY, unsigned numberOfRays);

        float getDistanceFromProjectionPlane(size_t screenWidth) const;

        const std::vector<unsigned int> &getWallStripHeights(float playerRotationAngle, unsigned d);
    };
}

#endif //RAYCASTING_RAYCASTING_H
