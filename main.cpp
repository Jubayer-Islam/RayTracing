#include <iostream>
#include <fstream>
//#include <__ranges/rend.h>
#include <ranges>
#include<chrono>

#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Screen.hpp"
#include "YourRayTracer.hpp"


int main() {
    const unsigned int width = 2560;
    const unsigned int height = 1600 ;
    Screen screen(width, height);
    Camera camera;
    camera.setEyePoint(vec3(0.0,1.0,-5.0));
    camera.setLookAt(vec3(0.0,0.0,0.0));

    Scene scene(vec3(0.0,0.0,0.0));

    Material black = Material(vec3(0.1, 0.1, 0.1), vec3(0.3, 0.3, 0.3), vec3(1, 1, 1), 8, 0.3);
    Material glass = Material(vec3(0.3, 0.3, 0.3), vec3(0.5, 0.5, 0.5), vec3(1, 1, 1), 8, 0.2, 1.52);
    Material mirror = Material(vec3(1.0, 1.0, 1.0), vec3(1,1,1), vec3(1, 1, 1), 8, 0.1);
    Material red = Material(vec3(1, 0, 0), vec3(1, 0, 0), vec3(1, 1, 1), 8, 0.8);
    Material cyan = Material(vec3(0, 1, 1), vec3(0, 1, 1), vec3(1, 1, 1), 8, 0.8);
    Material yellow = Material(vec3(1, 1, 0), vec3(1, 1, 0), vec3(1, 1, 1), 8, 0.8);
    Material green = Material(vec3(0, 1, 0), vec3(0, 1, 0), vec3(1, 1, 1), 8, 0.8);
    Material white = Material(vec3(0.3, 0.3, 0.3), vec3(0.5, 0.5, 0.5), vec3(1, 1, 1), 8, 0.8);

    Sphere s1 = Sphere(0.5, vec3{2,-1,2.5},  white); //unlike praktikum 03: HitSpheres, now our spheres have user defined colors, our spheres now can have shades, reflective and refractive properties
    Sphere s2 = Sphere(1.0, vec3{-5, -1, 6.2},  red);
    Sphere s3 = Sphere(1.0, vec3{7, -1, 8},  cyan);
    Sphere s4 = Sphere(1.0, vec3{-12.9, -1, 25.2}, yellow);
    Sphere s5 = Sphere(1.0, vec3{2.9, -1, 15.2},  green);

    Sphere s_glass = Sphere(2, vec3{-1,-1,2.5},  glass); //only glass has IOR=1.52,meaning the material allows refraction (i.e. glass or water). Other spheres' IOR is 0 by default
    Sphere s_mirror = Sphere(2, vec3{5,-1,10.5},  mirror); //small black sphere at the back

    Sphere spheres[7] = {s1, s2, s3, s4, s5, s_glass, s_mirror};

    for(auto sphere: spheres) {
        scene.addSphere(sphere);
    }
    YourRayTracer renderer(9); // same rendering like the last project, additionally we only try to find the runtime for the actual rendering process using chrono library
    renderer.setCamera(camera);
    renderer.setScene(scene);
    auto start = std::chrono::system_clock::now();
    // Some computation here
    renderer.render(screen);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;

    screen.saveAsPNG("screen.png");
    return 0;
}
