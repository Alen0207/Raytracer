/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include <exception>
#include "../include/Renderer.hpp"
#include "../include/SceneBuilder.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << "./raytracer <SCENE_FILE>" << std::endl;
        return 84;
    }
    try {
        RayTracer::SceneBuilder builder;
        RayTracer::Scene scene = builder.build(argv[1]);
        RayTracer::Renderer renderer(scene);

        renderer.render();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}