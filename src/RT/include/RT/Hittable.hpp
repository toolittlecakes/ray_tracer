
#ifndef RAY_TRACER_HITTABLE_HPP
#define RAY_TRACER_HITTABLE_HPP

#include "HitRecord.hpp"
#include <optional>

namespace RT {
    class Ray;

    struct Hittable {
        [[nodiscard]] virtual std::optional<HitRecord> hit(const Ray &ray) const = 0;

        virtual ~Hittable() = default;
    };

}

#endif //RAY_TRACER_HITTABLE_HPP
