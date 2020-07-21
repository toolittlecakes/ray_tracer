#ifndef RAY_TRACER_RAY_HPP
#define RAY_TRACER_RAY_HPP

#include "Vec3.hpp"

namespace RT {

    struct Ray {
        Vec3 origin;
        Vec3 direction;
        Ray(const Vec3& origin, const Vec3& direction)
                : origin(origin), direction(direction)
        {}
        Vec3 operator()(float t) const {
            return origin + direction * t;
        }
    };



}
#endif //RAY_TRACER_RAY_HPP
