/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Math
*/

#ifndef MYPROJECT_MATH_H
    #define MYPROJECT_MATH_H
    #include <cmath>

namespace Math
{
    class Vector3D
    {
        public:
            Vector3D() : X(0), Y(0), Z(0) {}
            Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}
            ~Vector3D() = default;

            double X;
            double Y;
            double Z;

            [[nodiscard]] double length() const noexcept
            {
                return std::sqrt(X * X + Y * Y + Z * Z);
            }

            [[nodiscard]] double dot(const Vector3D &v) const noexcept
            {
                return X * v.X + Y * v.Y + Z * v.Z;
            }

            // --- arithmetic operators ---

            [[nodiscard]] Vector3D operator+(const Vector3D &v) const noexcept
            {
                return {X + v.X, Y + v.Y, Z + v.Z};
            }
            void operator+=(const Vector3D &v) noexcept
            {
                X += v.X;
                Y += v.Y;
                Z += v.Z;
            }

            [[nodiscard]] Vector3D operator-(const Vector3D &v) const noexcept
            {
                return {X - v.X, Y - v.Y, Z - v.Z};
            }
            void operator-=(const Vector3D &v) noexcept
            {
                X -= v.X;
                Y -= v.Y;
                Z -= v.Z;
            }

            [[nodiscard]] Vector3D operator*(const Vector3D &v) const noexcept
            {
                return {X * v.X, Y * v.Y, Z * v.Z};
            }
            void operator*=(const Vector3D &v) noexcept
            {
                X *= v.X;
                Y *= v.Y;
                Z *= v.Z;
            }

            [[nodiscard]] Vector3D operator/(const Vector3D &v) const noexcept
            {
                return {
                    v.X == 0.0 ? 0.0 : X / v.X,
                    v.Y == 0.0 ? 0.0 : Y / v.Y,
                    v.Z == 0.0 ? 0.0 : Z / v.Z
                };
            }
            void operator/=(const Vector3D &v) noexcept
            {
                X /= v.X;
                Y /= v.Y;
                Z /= v.Z;
            }

            [[nodiscard]] Vector3D operator*(double s) const noexcept
            {
                return {X * s, Y * s, Z * s};
            }
            void operator*=(double s) noexcept
            {
                X *= s;
                Y *= s;
                Z *= s;
            }

            [[nodiscard]] Vector3D operator/(double s) const noexcept
            {
                return {X / s, Y / s, Z / s};
            }
            void operator/=(double s) noexcept
            {
                X /= s;
                Y /= s;
                Z /= s;
            }

            [[nodiscard]] Vector3D unit_vector() const
            {
                double len = length();

                if (len == 0.0)
                    return {0, 0, 0};
                return *this / len;
            }
    };
}

#endif //MYPROJECT_MATH_H
