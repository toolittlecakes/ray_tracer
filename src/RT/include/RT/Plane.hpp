#ifndef RAY_TRACER_PLANE_HPP
#define RAY_TRACER_PLANE_HPP

#include "Hittable.hpp"
#include "Material.hpp"

namespace RT {

    class Plane : public Hittable {

        Vec3 origin;
        Vec3 base1, base2;
        const Material &material;
    public:
        Plane(Vec3 origin, Vec3 base1, Vec3 base2, const Material &material)
                : origin(origin), base1(base1), base2(base2), material(material) {}


        [[nodiscard]]
        std::optional<HitRecord> hit(const Ray &ray) const override {
            Vec3 l0 = ray.origin;
            Vec3 l = ray.direction;
            Vec3 p0 = origin;
            Vec3 norm = base1.cross(base2).norm();
            float t = (p0 - l0).dot(norm) / l.dot(norm);


            Vec3 point = ray(t);

            auto local_point = point - origin;

            Vec3 acc{};
            auto cross1 = base1.cross(local_point);
            auto cross2 = base2.cross(local_point - base1);
            auto cross3 = (Vec3{} - base1).cross(local_point - base1 - base2);
            auto cross4 = (Vec3{} - base2).cross(local_point - base2);
            acc = cross1 + cross2 + cross3 + cross4;
            if (cross1.dot(norm) > 0 && cross2.dot(norm) > 0 && cross3.dot(norm) > 0 && cross4.dot(norm) > 0 &&
                    (acc / 2. + base2.cross(base1)).length() < 1e-5) {

                std::optional<Ray> next;
                auto scattered = material.scatter(ray.direction, norm);
                if(scattered.has_value()) {
                    next = Ray{point, scattered.value()};
                }
                auto attenuation = material.attenuation();
                auto emission = material.emission();
                return HitRecord{t, next, attenuation, emission};
            }
            return {};
        }

    };
}

#endif //RAY_TRACER_PLANE_HPP
