/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Shadows
*/

#ifndef MYPROJECT_SHADOWS_HPP
#define MYPROJECT_SHADOWS_HPP

#include <vector>
#include "interfaces/IPrimitive.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer
{
    class Shadows
    {
        public:
            Shadows(Math::Point3D hit, Math::Point3D lpos,
                const std::vector<std::unique_ptr<IPrimitive>> &prims,
                IPrimitive *curr, Math::Vector3D normal)
                : _hitpoint(hit), _lightpos(lpos),
                  _prims(prims), _self(curr), _normal(normal) {}

            ~Shadows() = default;

            bool isShadow();

        private:
            Math::Point3D _hitpoint;
            Math::Point3D _lightpos;
            const std::vector<std::unique_ptr<IPrimitive>> &_prims;
            IPrimitive *_self;
            Math::Vector3D _normal;
    };

    inline bool Shadows::isShadow()
    {
        Math::Vector3D tolight = {
            _lightpos.X - _hitpoint.X,
            _lightpos.Y - _hitpoint.Y,
            _lightpos.Z - _hitpoint.Z
        };
        double dist = tolight.length();
        if (dist == 0.0)
            return false;
        Math::Point3D shadow_origin = {
            _hitpoint.X + _normal.X * 1e-3,
            _hitpoint.Y + _normal.Y * 1e-3,
            _hitpoint.Z + _normal.Z * 1e-3
        };
        Ray shadow(shadow_origin, tolight / dist);

        for (const auto &p : _prims) {
            if (p.get() == _self)
                continue;
            double t = p->hits(shadow);
            if (t > 0.0 && t < dist)
                return true;
        }
        return false;
    }
}

#endif //MYPROJECT_SHADOWS_HPP
