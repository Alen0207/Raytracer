/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** ILight
*/

#ifndef MYPROJECT_ILIGHT_HPP
    #define MYPROJECT_ILIGHT_HPP
    #include "../Color.hpp"
    #include "../Point3D.hpp"

namespace RayTracer
{
    class ILight
    {
    public:
        ILight() = default;
        virtual ~ILight() = default;

        [[nodiscard]] virtual Math::Point3D getPosition(int pos) const = 0;
        [[nodiscard]] virtual double getIntensity(int pos) const = 0;
        [[nodiscard]] virtual ColorRGB getColor(int pos) const = 0;

        /**
         *
         * @return the coefficient of the darkness to apply
         */
        // [[nodiscard]] virtual double computeLight() const = 0;


    };
}

#endif //MYPROJECT_ILIGHT_HPP
