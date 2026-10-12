/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#include "../include/Renderer.hpp"
#include "../include/Color.hpp"
#include "../include/Shadows.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace RayTracer
{
    Renderer::Renderer(const Scene &scene) : _scene(scene)
    {
        for (const auto &p : _scene.primitives)
            _all.push_back(p.get());
    }

    void Renderer::render() const
    {
        IPrimitive *closest;
        double closestT;
        double u, v;
        Ray r;

        std::cout << "P3\n" << _scene.width << ' ' << _scene.height << "\n255\n";
        for (int i = 0; i < _scene.height; i++) {
            for (int j = 0; j < _scene.width; j++) {
                u = double(j) / double(_scene.width);
                v = 1.0 - double(i) / double(_scene.height);
                r = _scene.cam.ray(u, v);
                closestT = -1.0;
                closest = getClosest(r, closestT);
                if (closest)
                    writeColor(computeColor(closest, r, closestT));
                else
                    writeColor({0.5, 0.7, 1.0});
            }
        }
    }

    IPrimitive *Renderer::getClosest(const Ray &r, double &closestT) const
    {
        IPrimitive *closest = nullptr;
        double t;

        for (IPrimitive *prim : _all) {
            t = prim->hits(r);
            if (t > 0.0 && (closestT < 0.0 || t < closestT)) {
                closestT = t;
                closest = prim;
            }
        }
        return closest;
    }

    Math::Vector3D Renderer::computeColor(IPrimitive *prim,
        Ray &r, double t) const
    {
        Math::Point3D hitPoint = r.at(t);
        Math::Vector3D normal = prim->getNormal(hitPoint);
        Color primColor(prim->getColor());
        double r_out = _scene.ambientLight * primColor.r;
        double g_out = _scene.ambientLight * primColor.g;
        double b_out = _scene.ambientLight * primColor.b;
        double cosAngle;

        for (const auto &lightPos : _scene.pointLights) {
            Shadows shadow(hitPoint, lightPos, _scene.primitives, prim, normal);
            if (shadow.isShadow())
                continue;
            Math::Vector3D toLight = {
                lightPos.X - hitPoint.X,
                lightPos.Y - hitPoint.Y,
                lightPos.Z - hitPoint.Z
            };
            double dist = toLight.length();
            if (dist == 0.0)
                continue;
            toLight = toLight / dist;
            cosAngle = toLight.dot(normal);
            if (cosAngle <= 0.0)
                continue;
            r_out += cosAngle * primColor.r;
            g_out += cosAngle * primColor.g;
            b_out += cosAngle * primColor.b;
        }

        return {
            std::max(0.0, std::min(1.0, r_out)),
            std::max(0.0, std::min(1.0, g_out)),
            std::max(0.0, std::min(1.0, b_out))
        };
    }

    void Renderer::writeColor(Math::Vector3D color) const
    {
        std::cout
            << int(255 * std::max(0.0, std::min(1.0, color.X))) << ' '
            << int(255 * std::max(0.0, std::min(1.0, color.Y))) << ' '
            << int(255 * std::max(0.0, std::min(1.0, color.Z))) << '\n';
    }
}
