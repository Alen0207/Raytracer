/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Ray
*/


#ifndef MYPROJECT_RAY_HPP
    #define MYPROJECT_RAY_HPP
    #include "Point3D.hpp"
    #include "Vector3D.hpp"

namespace RayTracer
{
    class Ray
    {
        public:
            Ray(){origin = {0, 0, 0}, direction = {0, 0, 0};}
            Ray(const Math::Point3D &newOrigin, const Math::Vector3D &newDirection) {
                origin = newOrigin;
                direction = newDirection;
            }
            ~Ray() = default;

            //Attributes
            Math::Point3D origin;
            Math::Vector3D direction;

            /**
             * return coords of were the ray hit
             * @param double t
             * @return Point3D
             */
            Math::Point3D at(double t)
            {
                return origin + direction * t;
            }
    };
}

#endif
