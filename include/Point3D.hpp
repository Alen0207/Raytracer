/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Point3D
*/

#ifndef MYPROJECT_POINT3D_H
    #define MYPROJECT_POINT3D_H
    #include "Vector3D.hpp"

namespace Math
{
    class Point3D
    {
        public:
            Point3D() {X = 0; Y = 0; Z = 0;}
            Point3D(const double x, const double y, const double z) {
                    X = x;
                    Y = y;
                    Z = z;
            }
            ~Point3D() = default;

            //Attributes
            double X;
            double Y;
            double Z;

            //Overloaded operators
            Point3D operator+(const Vector3D &vec) const noexcept {
                return Point3D{
                    X + vec.X,
                    Y + vec.Y,
                    Z + vec.Z
                };
            }
            void operator+=(const Vector3D &vec) noexcept {
                X += vec.X;
                Y += vec.Y;
                Z += vec.Z;
            }
            Point3D operator-(const Vector3D&vec) const noexcept {
                return Point3D{
                    X - vec.X,
                    Y - vec.Y,
                    Z - vec.Z
                };
            }
            void operator-=(const Vector3D &vec) noexcept{
                    X -= vec.X;
                    Y -= vec.Y;
                    Z -= vec.Z;
            }
            Vector3D operator-(const Point3D &p) const noexcept
            {
                return Vector3D{
                    X - p.X,
                    Y - p.Y,
                    Z - p.Z
                };
            }
    };
}

#endif //MYPROJECT_POINT3D_H
