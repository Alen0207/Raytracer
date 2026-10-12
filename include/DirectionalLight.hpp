/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** DirectionalLight
*/

#ifndef MYPROJECT_DIRECTIONAL_LIGHT_HPP
    #define MYPROJECT_DIRECTIONAL_LIGHT_HPP

#include "Color.hpp"
#include "interfaces/ILight.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include "Parsing.hpp"

using DIR_LIGHT = std::tuple<COORD, double, RayTracer::ColorRGB>;

namespace RayTracer
{
    class DirectionalLight : public ILight
    {
    public:
        DirectionalLight(Math::Vector3D norm, Math::Point3D hit)
        {
            normal = norm;
            hitpoint = hit;
        }
        ~DirectionalLight() override = default;

        Math::Point3D getPosition(int pos) const override
        {
            return {
                std::get<0>(std::get<0>(_test[pos])),
                std::get<1>(std::get<0>(_test[pos])),
                std::get<2>(std::get<0>(_test[pos]))
            };
        }
        double getIntensity(int pos) const override { return std::get<1>(_test[pos]); }
        ColorRGB getColor(int pos) const override { return std::get<2>(_test[pos]); }
        ColorRGB computeLight() const;

        Math::Vector3D normal;
        Math::Point3D hitpoint;
        std::vector<DIR_LIGHT> _test =
            {{{1, 0.2, 0}, 0.8, {1, 1.0, 1.0}}};
    };

    inline ColorRGB DirectionalLight::computeLight() const
    {
        Math::Point3D pointlight = getPosition(0);
        double intensity = getIntensity(0);
        Color lightcolor(getColor(0));
        Math::Vector3D tolight(pointlight.X, pointlight.Y, pointlight.Z);
        double va_a = sqrt(tolight.X * tolight.X + tolight.Y * tolight.Y + tolight.Z * tolight.Z);
        double va_b = sqrt(normal.X * normal.X + normal.Y * normal.Y + normal.Z * normal.Z);
        double cosAngle;
        double diffuse;

        if (va_a == 0.0 || va_b == 0.0)
            return {0, 0, 0};
        cosAngle = tolight.dot(normal) / (va_a * va_b);
        if (cosAngle <= 0)
            return {0, 0, 0};
        diffuse = cosAngle * intensity;
        return {diffuse * lightcolor.r, diffuse * lightcolor.g, diffuse * lightcolor.b};
    }
}

#endif
