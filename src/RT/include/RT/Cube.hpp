//
// Created by sne on 5/30/20.
//

#ifndef RAY_TRACER_CUBE_HPP
#define RAY_TRACER_CUBE_HPP

#include "Hittable.hpp"
#include "Plane.hpp"

namespace RT {
    class Cube : public Hittable {
        std::vector<Plane> planes;
    public:
        Cube(Vec3 origin, Vec3 base1, Vec3 base2, Vec3 base3, const Material& material) {
//            planes.emplace_back(origin, base2, base1, material);
//            planes.emplace_back(origin + base3, base1, base2, material);
//            planes.emplace_back(origin, base3, base1, material);
//            planes.emplace_back(origin + base2, base1, base3, material);
//            planes.emplace_back(origin, base2, base3, material);
//            planes.emplace_back(origin + base1, base3, base2, material);
        }

        [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray) const override {
            float t = MAXFLOAT;
            std::optional < HitRecord > result;
            for (auto &plane : planes) {
                auto record = plane.hit(ray);
                if (record.has_value()) {
                    if (0 < record->t && record->t < t) {
                        t = record->t;
                        result = std::move(record);
                    }
                }
            }
            return result;
        }
    };


}

#endif //RAY_TRACER_CUBE_HPP
