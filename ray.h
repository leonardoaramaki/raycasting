#ifndef RAYCASTING_RAY_H
#define RAYCASTING_RAY_H

#include <SDL.h>
#include <vector>
#include "raycasting_data.h"
#include "map.h"

namespace rc {
    class Ray {
    private:
        bool _drawVertIntersectionPoints = false;
        bool _drawHorizIntersectionPoints = false;
        bool _drawCollisionPoints = false;
        float _angleInRadians;
        long _originX = 0;
        long _originY = 0;
        unsigned _distance = 1000;
        std::vector<rc::IntersectionPoint> _horizontalIntersectionPoints;
        std::vector<rc::IntersectionPoint> _verticalIntersectionPoints;
        std::vector<rc::CollisionPoint> _collisionPoints;

    private:
        void checkHorizontalIntersects(const Map &map);
        void checkVerticalIntersects(const Map &map);

    public:
        explicit Ray(float angle, float originX, float originY)
                : _angleInRadians(angle), _originX(originX), _originY(originY) {}

    public:
        bool cast(const Map& map);

        unsigned distance() const {
            return _distance;
        };

        float angleInRadians() const {
            return _angleInRadians;
        }

        void render(SDL_Renderer *renderer, unsigned originX, unsigned originY) const;

        void setDistance(int newDistance);
    };
}


#endif //RAYCASTING_RAY_H
