#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <RT/Vec3.hpp>
#include <cstdint>
#include <array>
#include <ostream>
#include <vector>

namespace RT {

    struct Color {
        using u8 = std::uint8_t;
        u8 r, g, b;

        Color(u8 r, u8 g, u8 b) : r{r}, g{g}, b{b} {}
        Color() = default;
        explicit Color(Vec3 v) {
            r = static_cast<u8>(fabsf(roundf(v.x * 255)));
            g = static_cast<u8>(fabsf(roundf(v.y * 255)));
            b = static_cast<u8>(fabsf(roundf(v.z * 255)));
        }


    };

    inline std::ostream &operator<<(std::ostream &out, RT::Color col) {
        return out << static_cast<std::uint16_t>(col.r) << ' '
                   << static_cast<std::uint16_t>(col.g) << ' '
                   << static_cast<std::uint16_t>(col.b);
    }

    class Image {
        std::vector<Color> data{};
        size_t width;
        size_t height;
    public:
        Image(size_t width, size_t height) : width(width), height(height), data(width * height){}
        Color &operator[](std::pair<size_t, size_t> indexes) {
            return data[indexes.first * width + indexes.second];
        }
        const Color &operator[](std::pair<size_t, size_t> indexes) const {
            return data[indexes.first * width + indexes.second];
        }
        void print_ppm(std::ostream &output) const {
            output << "P3" << std::endl;
            output << width << ' ' << height << std::endl;
            output << 255 << std::endl;
            for (size_t i = height; i > 0; i--) {
                for (size_t j = 0; j < width; j++) {
                    output << operator[]({i - 1, j}) << std::endl;
                }
            }
        }

    };
}


#endif //RAY_TRACER_IMAGE_HPP
