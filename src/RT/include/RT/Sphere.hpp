
#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP


#include "Hittable.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Material.hpp"

namespace RT {
    class Sphere : public Hittable {
        Vec3 center;
        float radius;
        const Material &material;
    public:
        Sphere(Vec3 center, float radius, const Material &material)
                : center(center), radius(radius), material(material) {}

        [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray) const override {
            Vec3 oc = ray.origin - center;
            auto a = ray.direction.dot(ray.direction);
            auto b = oc.dot(ray.direction) ;
            auto c = oc.dot(oc) - radius * radius;
            auto discriminant = b * b - a * c;
            if (discriminant > 0.) {

                float temp = (-b - std::sqrt((b * b - a * c))) / a;
                if (temp < 1e-5) {
                    temp = (-b + std::sqrt((b * b - a * c))) / a;
                    if (temp < 1e-5) {
                        return {};
                    }
                }
                Vec3 point = ray(temp);
                Vec3 norm = (point - center).norm();
                auto scattered = material.scatter(ray.direction, norm);
                std::optional<Ray> next{};
                if(scattered.has_value()) {
                    next = Ray{point, scattered.value()};
                }
                auto attenuation = material.attenuation();
                auto emission = material.emission();
                if (emission.has_value()) {
                    int x = 0;
                }
                return HitRecord{temp, next, attenuation, emission};
            }
            return {};
        }
    };

}
#endif //RAY_TRACER_SPHERE_HPP
