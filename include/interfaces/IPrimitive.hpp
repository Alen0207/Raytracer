/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** IPrimitive
*/


#ifndef MYPROJECT_IPRIMITIVE_HPP
#define MYPROJECT_IPRIMITIVE_HPP
    #include <string>
    #include "IMaterial.hpp"
    #include "../Ray.hpp"
    #include "../Color.hpp"
    #include <memory>

namespace RayTracer
{
    class IPrimitive
    {
    public:
        virtual ~IPrimitive() = default;

        [[nodiscard]] virtual double hits(const Ray &ray) const = 0;
        [[nodiscard]] virtual std::shared_ptr<IMaterial> getMaterial() const = 0;
        [[nodiscard]] virtual std::string getName() const = 0;
        [[nodiscard]] virtual Math::Vector3D getPosition() const = 0;
        [[nodiscard]] virtual ColorRGB getColor() const = 0;
        [[nodiscard]] virtual Math::Vector3D getNormal(const Math::Point3D &hitPoint) const = 0;

    protected:
        std::shared_ptr<IMaterial> _material;
        std::string _name;
        Math::Vector3D _position;
        ColorRGB _color;
    };
}

#endif //MYPROJECT_IPRIMITIVE_HPP
