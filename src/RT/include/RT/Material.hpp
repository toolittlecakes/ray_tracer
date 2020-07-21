
#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include "Ray.hpp"
#include "Random.hpp"

namespace RT {

    class Material {
    public:
        [[nodiscard]] virtual std::optional<Vec3> scatter(Vec3 in, Vec3 norm) const { return {}; }

        [[nodiscard]] virtual std::optional<Vec3> attenuation() const { return {}; }

        [[nodiscard]] virtual std::optional<Vec3> emission() const { return {}; }


        virtual ~Material() = default;
    };

    class Diffuse : public Material {
        Vec3 albedo;

    public:
        explicit Diffuse(const Vec3 &albedo) : albedo(albedo) {}

        [[nodiscard]]
        std::optional<Vec3> attenuation() const override { return albedo; }

        [[nodiscard]]
        std::optional<Vec3> scatter(Vec3 in, Vec3 norm) const override {
            return (norm * (-in.dot(norm))).norm() + Random::random_in_unit_sphere();
        }
    };

    class Metallic : public Material {
        Vec3 albedo;
        float fuzz;
    public:
        Metallic(const Vec3 &albedo, float fuzz = 0.f) : albedo(albedo), fuzz(fuzz) {}

        Metallic() : Metallic(Vec3{1.f, 1.f, 1.f}, 0.f) {}

        [[nodiscard]]
        std::optional<Vec3> attenuation() const override { return albedo; }

        [[nodiscard]]
        std::optional<Vec3> scatter(Vec3 in, Vec3 norm) const override {
            return in - norm * (in.dot(norm)) * 2. + Random::random_in_unit_sphere() * fuzz;
        }
    };
    class Emissive : public Material {
        Vec3 albedo;
    public:
        Emissive(const Vec3 &albedo) : albedo(albedo) {}

        Emissive() : Emissive(Vec3{1.f, 1.f, 1.f}) {}

        [[nodiscard]]
        std::optional<Vec3> emission() const override { return albedo; }

    };



}

#endif //RAY_TRACER_MATERIAL_HPP
