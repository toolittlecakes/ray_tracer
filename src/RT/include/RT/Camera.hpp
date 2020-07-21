
#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include "Ray.hpp"
#include "Vec3.hpp"
#include "Image.hpp"
#include "Hittable.hpp"
#include "Random.hpp"
#include <cmath>
#include <random>

namespace RT {

    class Camera {
        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u, v, w;
        float lens_radius;

    public:
        Camera(
                Vec3 look_from,
                Vec3 look_at,
                Vec3 view_up,
                float field_of_view,
                float aspect,
                float lens_radius,
                float focus_distance
        ) : origin(look_from), lens_radius(lens_radius) {
            float theta = field_of_view * static_cast<float>(M_PI) / 180.f;
            float height = std::tan(theta / 2.f) * 2.f;
            float width = aspect * height;

            w = (look_from - look_at).norm();
            u = view_up.cross(w).norm();
            v = w.cross(u);

            horizontal = u * width * focus_distance;
            vertical = v * height * focus_distance;
            lower_left_corner = look_from - horizontal / 2.f - vertical / 2.f - w * focus_distance;
        }

        [[nodiscard]] inline Ray get_ray(float s, float t) const {
            Vec3 rd = Random::random_in_unit_disk() * lens_radius;
            Vec3 offset = u * rd.x + v * rd.y;
            return Ray{origin + offset, lower_left_corner + vertical * s + horizontal * t - origin - offset};
        }
    };
}
#endif //RAY_TRACER_CAMERA_HPP
