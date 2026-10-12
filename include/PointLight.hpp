/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** PointLight
*/

#ifndef MYPROJECT_POINTLIGHT_HPP
#define MYPROJECT_POINTLIGHT_HPP
#include <vector>
#include <cmath>
#include <algorithm>
#include "Color.hpp"
#include "interfaces/ILight.hpp"

using POINT_LIGHT = std::tuple<Math::Point3D, double, RayTracer::ColorRGB>;

namespace RayTracer
{
    class PointLight : public ILight {
        public:
        PointLight(std::vector<POINT_LIGHT> vect, Math::Vector3D norm, Math::Point3D hit) : normal(norm), hitpoint(hit), lights(vect) {};
        ~PointLight() override = default;

        Math::Point3D getPosition(int pos) const override {return {std::get<0>(lights[pos])};}
        double getIntensity(int pos) const override {return std::get<1>(lights[pos]);};
        ColorRGB getColor(int pos) const override {return std::get<2>(lights[pos]);};
        ColorRGB computeLight() const;

        std::vector<POINT_LIGHT> lights = {{{400, 100, 500}, 0.8, {1, 1.0, 0.5}}};
        Math::Vector3D normal;
        Math::Point3D hitpoint;
    };

    inline ColorRGB PointLight::computeLight() const
    {
        Color res({0, 0, 0});
        double cosAngle;
        double intensity;
        double va_a;
        double va_b;

        for (size_t i = 0; i < lights.size(); i++) {
            Math::Point3D pos = getPosition(i);
            intensity = getIntensity(i);
            Color color(getColor(i));
            Math::Vector3D tolight(pos.X - hitpoint.X, pos.Y - hitpoint.Y, pos.Z - hitpoint.Z);
            va_a = sqrt(tolight.X * tolight.X + tolight.Y * tolight.Y + tolight.Z * tolight.Z);
            va_b = sqrt(normal.X * normal.X + normal.Y * normal.Y + normal.Z * normal.Z);
            if (va_a == 0.0 || va_b == 0.0)
                continue;
            cosAngle = tolight.dot(normal) / (va_a * va_b);
            if (cosAngle <= 0)
                continue;
            res.r += cosAngle * intensity * color.r;
            res.g += cosAngle * intensity * color.g;
            res.b += cosAngle * intensity * color.b;
        }
        res.r = std::min(1.0, res.r);
        res.g = std::min(1.0, res.g);
        res.b = std::min(1.0, res.b);
        return {res.r, res.g, res.b};
    }
}

#endif //MYPROJECT_POINTLIGHT_HPP
