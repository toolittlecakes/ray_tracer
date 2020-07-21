
#ifndef RAY_TRACER_HITTABLEOBJECTS_HPP
#define RAY_TRACER_HITTABLEOBJECTS_HPP

#include "Hittable.hpp"
#include "Plane.hpp"
#include "Cube.hpp"
#include <memory>
#include <vector>
#include <limits>
#include <unordered_map>

namespace RT {
    struct HittableObjects : Hittable {
        std::vector<std::unique_ptr<Hittable>> objects;
        void emplace_back(std::unique_ptr<Hittable>&& object) {
            objects.push_back(std::move(object));
        }
        [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray) const override {
            float t = MAXFLOAT;
            std::optional<HitRecord> result;
            for (auto &object : objects) {
                auto record = object->hit(ray);
                if (record.has_value()) {
                    if (1e-5 < record->t && record->t < t) {
                        t = record->t;
                        result = std::move(record);
                    }
                }
            }
            return result;
        }
    };
}

#endif //RAY_TRACER_HITTABLEOBJECTS_HPP
