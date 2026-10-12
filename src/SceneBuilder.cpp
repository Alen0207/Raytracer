/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#include "../include/SceneBuilder.hpp"
#include <cmath>

namespace RayTracer
{
    Scene SceneBuilder::build(const std::string &configFile)
    {
        Parsing parser(configFile);
        Scene scene;

        parser.parse();
        scene.cam = buildCamera(parser.getCam(), scene.width, scene.height);
        buildPrimitives(parser, scene);
        buildLights(parser, scene);
        return scene;
    }

    Camera SceneBuilder::buildCamera(const CAM &camData,
        int &outWidth, int &outHeight)
    {
        auto [dim, pos, rot, fov] = camData;
        auto [w, h] = dim;
        auto [px, py, pz] = pos;
        auto [rx, ry, rz] = rot;
        double ratio = w / h;
        double pitch = rx * M_PI / 180.0;
        double yaw = ry * M_PI / 180.0;
        Math::Point3D position = {px, py, pz};
        Math::Point3D target = {
            px + std::cos(pitch) * std::sin(yaw),
            py + std::cos(pitch) * std::cos(yaw),
            pz + std::sin(pitch)
        };

        outWidth = static_cast<int>(w);
        outHeight = static_cast<int>(h);
        return Camera(position, target, fov, ratio);
    }

    void SceneBuilder::buildPrimitives(Parsing &parser, Scene &scene)
    {
        for (const auto &s : parser.getSpheres())
            scene.primitives.push_back(_factory.createPrimitive(s));
        for (const auto &p : parser.getPlanes())
            scene.primitives.push_back(_factory.createPrimitive(p));
        for (const auto &c : parser.getCones())
            scene.primitives.push_back(_factory.createPrimitive(c));
    }

    void SceneBuilder::buildLights(Parsing &parser, Scene &scene)
    {
        const auto &[ambient, diffuse, points] = parser.getLights();

        scene.ambientLight = ambient;
        for (const auto &p : points)
            scene.pointLights.push_back(p);
    }
}
