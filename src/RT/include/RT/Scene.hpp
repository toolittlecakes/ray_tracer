//
// Created by sne on 5/25/20.
//

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP


namespace RT {
    class HittableObjects;

    class Camera;

    class Tracer;

    class Scene final {
        Camera camera;
        HittableObjects objects;
    public:
        Scene(Camera camera, HittableObjects &&objects);

        [[nodiscard]] Image
        render(const Tracer &tracer, size_t width, size_t height, size_t samples_per_pixel = 100) const;
    };

}
#endif //RAY_TRACER_SCENE_HPP
