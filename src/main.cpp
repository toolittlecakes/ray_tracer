#include <iostream>
#include <RT/Camera.hpp>
#include <RT/Sphere.hpp>
#include <fstream>
#include <RT/HittableObjects.hpp>
#include <RT/Scene.hpp>
#include <map>
#include <RT/Tracer.hpp>


int main() {

    const size_t width = 1920/ 4 ;
    const size_t height = 1080/4 ;



    std::map<std::string, std::unique_ptr<RT::Material>> materials;
//    materials.insert({"mirror", std::make_unique<RT::Metallic>(RT::Vec3{.9, .9, .9}, 0.1)});
//    materials.insert({"lamp", std::make_unique<RT::Emissive>(RT::Vec3{.9, .4, .9})});
//    materials.insert({"lamp", std::make_unique<RT::Emissive>(RT::Vec3{.9, .4, .9})});
    RT::Metallic mirror{{.9, .9, .9}, 0.};
    RT::Diffuse tip{{.2, .2, .9}};

    RT::Emissive lamp{{.9, .6, .9}};
    RT::Emissive moon{{.8, .8, .8}};

    RT::Emissive sky{{0.01, 0.01, 0.02}};
    RT::Diffuse planet{{.4, .4, .6}};
    RT::Emissive dark{{.0, .0, .0}};


//    RT::Camera camera{
//            RT::Vec3{1, 2, 5},
//            RT::Vec3{0, 1, 0},
//            RT::Vec3{0, 1, 0},
//            30,
//            static_cast<float>(width) / height,
//            0.02,
//            5
//    };
    RT::Camera camera{
            RT::Vec3{0, 0, 0},
            RT::Vec3{0, 1, 0},
            RT::Vec3{0, 0, 1},
            170,
            static_cast<float>(width) / height,
            0.02,
            5
    };
    RT::HittableObjects objects;
    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{0, 0, -39}, .1f, moon));

//    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{-3.5, 2.5f, -1.f}, .7f, mirror));
//    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{4, 4, -9.f}, .7f, moon));
//
//    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{0.f, 1.f, 0.f}, 1.f, tip));
    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{0.f, -100.f, 0.f}, 140.f, sky));
//    objects.emplace_back(std::make_unique<RT::Sphere>(RT::Vec3{0, -100, 0}, 100.f, planet));
//
    for(size_t i = 0; i < 1000; i++) {
        RT::Vec3 center{};
        do {
            center = RT::Random::random_unit_vector() * 139;
        } while(center.y < 100 || center.z > 50);

        center.y = center.y - 100;
        objects.emplace_back(std::make_unique<RT::Sphere>(center, 0.02f * (1.f + RT::Random::random_float()), moon));

    }
//
//    objects.emplace_back(std::make_unique<RT::Plane>(
//            RT::Vec3{2, 0.3, -3.5},
//            RT::Vec3{0, 2, 0},
//            RT::Vec3{3.5, 0, 3},
//            mirror
//    ));
//    objects.emplace_back(std::make_unique<RT::Plane>(
//            RT::Vec3{2-3.5*0.01, 0.3-0.03, -3.5 -3*0.01},
//            RT::Vec3{0, 2+0.06, 0},
//            RT::Vec3{3.5, 0, 3},
//            dark
//    ));
//    size_t n = 6;
//    for (size_t i = 0; i < n; i++) {
//        float angle = M_PI * 2 / n * i;
//        objects.emplace_back(
//                std::make_unique<RT::Sphere>(RT::Vec3{1.5f * cosf(angle), 0.2f, 1.5f * sinf(angle)}, 0.1f, lamp));
//    }


    RT::Scene scene(camera, std::move(objects));
    RT::ForwardTracer tracer;


    auto image = scene.render(tracer, width, height, 300);
    std::fstream out("out.ppm", std::ios::out | std::ios::trunc);
    image.print_ppm(out);
    return 0;
}
