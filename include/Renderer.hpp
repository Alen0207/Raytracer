/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
    #define RENDERER_HPP_

#include "SceneBuilder.hpp"
#include "interfaces/IPrimitive.hpp"
#include "Ray.hpp"
#include <vector>

namespace RayTracer
{
    class Renderer
    {
        public:
            explicit Renderer(const Scene &scene);
            void render() const;

            void buildList();
            IPrimitive *getClosest(const Ray &r, double &closestT) const;
            Math::Vector3D computeColor(IPrimitive * prim, Ray &r, double t) const;
            void writeColor(Math::Vector3D color) const;

        private:
            const Scene &_scene;
            std::vector<IPrimitive *> _all;
    };
}

#endif /* !RENDERER_HPP_ */
