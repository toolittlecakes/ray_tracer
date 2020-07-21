//
// Created by sne on 5/24/20.
//
#include <iostream>
#include "RT/Camera.hpp"
#include "RT/HittableObjects.hpp"
#include "RT/Tracer.hpp"
#include "RT/Image.hpp"
#include "RT/Scene.hpp"

RT::Image RT::Scene::render(const RT::Tracer &tracer, size_t width, size_t height, size_t samples_per_pixel) const {
    RT::Image res{width, height};

    for (size_t i = 0; i < height; i++) {
        std::cout << i << std::endl;
        for (size_t j = 0; j < width; j++) {
            Vec3 color{};

            for (size_t n = 0; n < samples_per_pixel; n++) {
                float s = (i + Random::random_float()) / (height);
                float t = (j + Random::random_float()) / (width);

                auto ray = camera.get_ray(s, t);
                color = color + tracer.trace(ray, objects).sqr();
            }
            res[{i, j}] = Color{(color / samples_per_pixel).sqrt().sqrt()};
        }
    }
    return res;
}

RT::Scene::Scene(RT::Camera camera, RT::HittableObjects &&objects) : camera(camera), objects(std::move(objects)){}
