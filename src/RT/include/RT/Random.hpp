//
// Created by sne on 5/24/20.
//

#ifndef RAY_TRACER_RANDOM_HPP
#define RAY_TRACER_RANDOM_HPP

#include "Vec3.hpp"
#include <random>
namespace  RT {
    class Random {
    public:
        static inline float random_float() {

            return static_cast<float>(rand() / (RAND_MAX + 1.));
        }
        static inline float random_float(float min, float max) {
            // Returns a random real in [min,max).
            return min + (max-min)*random_float();
        }

        static Vec3 random_unit_vector() {
            float a = random_float(0, 2 * M_PI);
            float z = random_float(-1, 1);
            float r = std::sqrt(1 - z * z);
            return Vec3(r * cosf(a), r * sinf(a), z);
        }

        static Vec3 random_in_unit_sphere() {
            return random_unit_vector() * sqrtf(random_float());
        }


        static Vec3 random_in_unit_disk() {
            float a = random_float(0, 2 * M_PI);
            float r_sqrt = sqrtf(random_float());
            return Vec3{r_sqrt * cosf(a), r_sqrt * sinf(a), 0.f};
        }

//        Vec3 random_in_hemisphere(const Vec3 &normal) {
//            Vec3 in_unit_sphere = random_in_unit_sphere();
//            if (in_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
//                return in_unit_sphere;
//            else
//                return Vec3{} - in_unit_sphere;
//        }

    };
}

#endif //RAY_TRACER_RANDOM_HPP
