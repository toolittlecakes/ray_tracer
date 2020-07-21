cmake_minimum_required(VERSION 3.16)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/RT/include/)

add_executable(ray_tracer src/main.cpp src/RT/include/RT/Vec3.hpp src/RT/src/Scene.cpp src/RT/include/RT/Image.hpp src/RT/include/RT/Camera.hpp src/RT/include/RT/Ray.hpp src/RT/include/RT/Hittable.hpp  src/RT/include/RT/Sphere.hpp src/RT/include/RT/Material.hpp src/RT/include/RT/HitRecord.hpp src/RT/include/RT/HittableObjects.hpp src/RT/include/RT/Random.hpp  "src/RT/include/RT/Scene.hpp" src/RT/include/RT/Plane.hpp src/RT/include/RT/Cube.hpp src/RT/include/RT/Tracer.cpp src/RT/include/RT/Tracer.hpp)