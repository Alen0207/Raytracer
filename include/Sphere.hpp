/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef MYPROJECT_SPHERE_HPP
    #define MYPROJECT_SPHERE_HPP

    #include "interfaces/IPrimitive.hpp"
    #include "Point3D.hpp"
    #include "Ray.hpp"
    #include <cmath>
    #include <string>
    #include <memory>

namespace RayTracer
{
    class Sphere : public IPrimitive
    {
        public:
            Sphere()
            {
                origin = {0, 0, 0};
                radius = 0.0;
                _color = {1.0, 1.0, 1.0};
                _name = "sphere";
            }

            Sphere(const Math::Point3D &newOrigin, const double newRadius,
                   const ColorRGB &color = {1.0, 1.0, 1.0})
            {
                origin = newOrigin;
                radius = newRadius;
                _color = color;
                _name = "sphere";
            }

            ~Sphere() = default;

            Math::Point3D origin;
            double radius;

            [[nodiscard]] double hits(const RayTracer::Ray &ray) const override
            {
                Math::Vector3D oc = {
                    ray.origin.X - origin.X,
                    ray.origin.Y - origin.Y,
                    ray.origin.Z - origin.Z
                };
                double a = ray.direction.dot(ray.direction);
                double b = 2.0 * ray.direction.dot(oc);
                double c = oc.dot(oc) - radius * radius;
                double discriminant = b * b - 4.0 * a * c;

                if (discriminant < 0.0)
                    return -1.0;
                return (-b - std::sqrt(discriminant)) / (2.0 * a);
            }

            [[nodiscard]] Math::Vector3D getNormal(const Math::Point3D
                &hitPoint) const override
            {
                Math::Vector3D n = {
                    hitPoint.X - origin.X,
                    hitPoint.Y - origin.Y,
                    hitPoint.Z - origin.Z
                };
                double len = n.length();

                if (len > 0.0)
                    n /= len;
                return n;
            }

            [[nodiscard]] std::shared_ptr<IMaterial> getMaterial() const override
            {
                return  _material;
            }

            [[nodiscard]] std::string getName() const override
            {
                return _name;
            }

            [[nodiscard]] Math::Vector3D getPosition() const override
            {
                return {origin.X, origin.Y, origin.Z};
            }

            [[nodiscard]] ColorRGB getColor() const override
            {
                return _color;
            }
    };
}

#endif /* !MYPROJECT_SPHERE_HPP */
