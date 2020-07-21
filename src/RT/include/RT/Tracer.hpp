
#ifndef RAY_TRACER_TRACER_HPP
#define RAY_TRACER_TRACER_HPP

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hittable.hpp"

namespace RT {
    struct Tracer {
        virtual Vec3 trace(const Ray &ray, const Hittable &scene) const = 0;

        virtual ~Tracer() = default;
    };

    struct ForwardTracer : Tracer {
        size_t depth;

        explicit ForwardTracer(size_t depth = 10) : depth(depth) {}

        Vec3 trace(const Ray &ray, const Hittable &scene) const override {
            Vec3 res{1, 1, 1};
            Ray r = ray;
            for (size_t i = 0; i < depth; i++) {
                auto record = scene.hit(r);
                if (record.has_value()) {
                    auto rec = record.value();
                    if(rec.ray.has_value()) {
                        res = res * rec.attenuation.value_or(Vec3{1,1,1});
                        r = record->ray.value();
                    }
                    else {
                        res = res * rec.emission.value_or(Vec3{0,0,0});
                        return res;
                    }
                } else {
                    return {0,0,0};
                }
            }
            return {0,0,0};

        }
    };
}

#endif //RAY_TRACER_TRACER_HPP
