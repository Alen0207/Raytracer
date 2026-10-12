/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Plane
*/

#ifndef MYPROJECT_PLANE_HPP
    #define MYPROJECT_PLANE_HPP
    #include <memory>
    #include "interfaces/IPrimitive.hpp"
    #include "MaterialsFactory.hpp"

namespace RayTracer
{
    class Plane : public IPrimitive
    {
        public:
            Plane()
            {
                const MaterialsFactory factory;
                _position.X = 0;
                _position.Y = 0;
                _position.Z = 0;
                _color = {1.0, 1.0, 1.0};
                _name = "plane";
                _material = factory.createMaterial("flatColor");
            }
            Plane(const Math::Vector3D &pos, const ColorRGB &color)
            {
                const MaterialsFactory factory;
                _position = pos;
                _color = color;
                _name = "plane";
                _material = factory.createMaterial("flatColor");
            }
            Plane(const Plane &plane) = delete;
            ~Plane() override = default;

            [[nodiscard]] std::shared_ptr<IMaterial> getMaterial() const override
            {
                return _material;
            }

            [[nodiscard]] Math::Vector3D getPosition() const override
            {
                return _position;
            }

            [[nodiscard]] std::string getName() const override
            {
                return _name;
            }

            [[nodiscard]] ColorRGB getColor() const override
            {
                return _color;
            }

            [[nodiscard]] Math::Vector3D getNormal(const Math::Point3D &hitPoint) const override
            {
                (void)hitPoint;
                if (_position.X != 0.0)
                    return {1, 0, 0};
                if (_position.Y != 0.0)
                    return {0, 1, 0};
                return {0, 0, 1};
            }

            [[nodiscard]] double hits(const Ray &ray) const override
            {
                double direction = 0;
                double origin = 0;
                double t = -1;

                if (_position.X != 0) {
                    origin = ray.origin.X;
                    direction = ray.direction.X;
                    if (direction == 0)
                        return -1;
                    t = (_position.X - origin) / direction;
                }
                if (_position.Y != 0) {
                    origin = ray.origin.Y;
                    direction = ray.direction.Y;
                    if (direction == 0)
                        return -1;
                    t = (_position.Y - origin) / direction;
                }
                if (_position.Z != 0) {
                    origin = ray.origin.Z;
                    direction = ray.direction.Z;
                    if (direction == 0)
                        return -1;
                    t = (_position.Z - origin) / direction;
                }
                if (t < 0)
                    return -1;
                return t;
            }
    };
}

#endif //MYPROJECT_PLANE_HPP
