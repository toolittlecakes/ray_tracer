#ifndef RAY_TRACER_VEC3_HPP
#define RAY_TRACER_VEC3_HPP


#include <cmath>
#include <ostream>

namespace RT {

    struct Vec3 {
        float x, y, z;

        Vec3() = default;

        Vec3(float x, float y, float z) noexcept: x{x}, y{y}, z{z} {}

        float length() const noexcept {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vec3 operator+(const Vec3 &v) const {
            return {x + v.x, y + v.y, z + v.z};
        }

        Vec3 operator-(const Vec3 &v) const {
            return {x - v.x, y - v.y, z - v.z};
        }

        Vec3 operator*(const Vec3 &v) const {
            return {x * v.x, y * v.y, z * v.z};
        }

        Vec3 operator*(float t) const {
            return {t * x, t * y, t * z};
        }

        Vec3 operator/(float t) const {
            return *this * (1 / t);
        }

        float dot(const Vec3 &v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        Vec3 cross(const Vec3 &v) const {
            return {y * v.z - z * v.y,
                    z * v.x - x * v.z,
                    x * v.y - y * v.x};
        }


        static Vec3 cross(const Vec3 &u, const Vec3 &v) {
            return {u.y * v.z - u.z * v.y,
                    u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x};
        }

        static Vec3 unit_vector(Vec3 v) {
            return v / v.length();
        }

        Vec3 norm() const {
//            const float number = x * x + y * y + z * z;
//            const float x2 = number * 0.5f;
//            const float threehalfs = 1.5f;
//
//            union {
//                float f;
//                uint32_t i;
//            } conv = {number}; // member 'f' set to value of 'number'.
//            conv.i  = 0x5f3759df - ( conv.i >> 1 );
//            conv.f  *= ( threehalfs - ( x2 * conv.f * conv.f ) );
//            return *this * conv.f;
            return *this / length();
        }

        Vec3 sqrt() const {
            return {std::sqrt(x), std::sqrt(y), std::sqrt(z)};
        }
        Vec3 sqr() const {
            return {x*x, y*y, z*z};
        }
    };

    inline std::ostream &operator<<(std::ostream &out, Vec3 vec) {
        out << vec.x << ' ' << vec.y << ' ' << vec.z;
    }

}
#endif //RAY_TRACER_VEC3_HPP
