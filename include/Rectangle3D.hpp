/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Rectangle3D
*/

#ifndef MYPROJECT_RECTANGLE3D_HPP
    #define MYPROJECT_RECTANGLE3D_HPP
    #include "Point3D.hpp"
    #include "Vector3D.hpp"

namespace RayTracer
{
    class Rectangle3D
    {
        public:
            //variables
            Math::Point3D origin = {0, 0, 0};
            Math::Vector3D bottom_side = {1, 0 , 0};
            Math::Vector3D left_side = {0, 1, 0};

            Rectangle3D(Math::Point3D o, Math::Vector3D b,
                Math::Vector3D l) : origin(o), bottom_side(b), left_side(l)
            {}

            [[nodiscard]] Math::Point3D pointAt(const double u, const double v) const {
                return (origin + bottom_side * u + left_side * v);
            };
    };
}

#endif //MYPROJECT_RECTANGLE3D_HPP
