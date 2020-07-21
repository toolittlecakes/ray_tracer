
#ifndef RAY_TRACER_HITRECORD_HPP
#define RAY_TRACER_HITRECORD_HPP

#include <optional>
#include <utility>
#include "Ray.hpp"

namespace RT {

    struct HitRecord final {
        float t;
        std::optional<Ray> ray;
        std::optional<Vec3> attenuation;
        std::optional<Vec3> emission;

//        Vec3 emission;
        HitRecord(float t, std::optional<Ray> ray, std::optional<Vec3> attenuation, std::optional<Vec3> emission)
                : t(t),
                  ray(std::move(ray)),
                  attenuation(std::move(attenuation)),
                  emission(std::move(emission)) {}
    };
}

#endif //RAY_TRACER_HITRECORD_HPP
