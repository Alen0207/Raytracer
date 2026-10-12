/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#ifndef MYPROJECT_CONE_HPP
    #define MYPROJECT_CONE_HPP

    #include "interfaces/IPrimitive.hpp"
    #include "Point3D.hpp"
    #include "Ray.hpp"
    #include <cmath>
    #include <string>
    #include <memory>

namespace RayTracer
{
    class Cone : public IPrimitive
    {
        public:
            Cone()
            {
                apex = {0, 0, 0};
                halfAngle = M_PI / 6.0;
                _color = {1.0, 0.5, 0.0};
                _name = "cone";
                axis = "Z";
            }
            Cone(const Math::Point3D &apexPos, double angle,
                const ColorRGB &color = {1.0, 0.5, 0.0},
                const std::string &ax = "Z")
            {
                apex = apexPos;
                halfAngle = angle;
                _color = color;
                _name = "cone";
                axis = ax;
            }
            ~Cone() = default;

            Math::Point3D apex;
            double halfAngle;
            std::string axis;

            void getComponents(double ox, double oy, double oz,
                double dx, double dy, double dz,
                double &oAxis, double &oR1, double &oR2,
                double &dAxis, double &dR1, double &dR2) const
            {
                if (axis == "X") {
                    oAxis = ox;
                    oR1 = oy;
                    oR2 = oz;
                    dAxis = dx;
                    dR1 = dy;
                    dR2 = dz;
                } else if (axis == "Y") {
                    oAxis = oy;
                    oR1 = ox;
                    oR2 = oz;
                    dAxis = dy;
                    dR1 = dx;
                    dR2 = dz;
                } else {
                    oAxis = oz;
                    oR1 = ox;
                    oR2 = oy;
                    dAxis = dz;
                    dR1 = dx;
                    dR2 = dy;
                }
            }

        public:
            [[nodiscard]] bool isValidHit(double t, double oAxis, double dAxis) const
            {
                if (t <= 1e-4)
                    return false;
                return (oAxis + t * dAxis) <= 0.0;
            }

            [[nodiscard]] Math::Vector3D getNormal(const Math::Point3D &hitPoint) const override
            {
                double k = std::tan(halfAngle);
                double rx = hitPoint.X - apex.X;
                double ry = hitPoint.Y - apex.Y;
                double rz = hitPoint.Z - apex.Z;
                Math::Vector3D n;
                double len;

                if (axis == "X")
                    n = {-(k * k) * rx, ry, rz};
                else if (axis == "Y")
                    n = {rx, -(k * k) * ry, rz};
                else
                    n = {rx, ry, -(k * k) * rz};
                len = n.length();
                if (len > 0.0)
                    n = n / len;
                return n;
            }

            [[nodiscard]] double hits(const RayTracer::Ray &ray) const override
            {
                double k = std::tan(halfAngle);
                double ox = ray.origin.X - apex.X;
                double oy = ray.origin.Y - apex.Y;
                double oz = ray.origin.Z - apex.Z;
                double dx = ray.direction.X;
                double dy = ray.direction.Y;
                double dz = ray.direction.Z;
                double oAxis, oR1, oR2, dAxis, dR1, dR2;
                getComponents(ox, oy, oz, dx, dy, dz,
                    oAxis, oR1, oR2, dAxis, dR1, dR2);
                double a = dR1 * dR1 + dR2 * dR2 - k * k * dAxis * dAxis;
                double b = 2.0 * (oR1 * dR1 + oR2*dR2 - k * k * oAxis*dAxis);
                double c = oR1 * oR1 + oR2 * oR2 - k * k * oAxis * oAxis;
                double discriminant = b * b - 4.0 * a * c;
                double sqrtD = std::sqrt(discriminant);
                double t1 = (-b - sqrtD) / (2.0 * a);
                double t2 = (-b + sqrtD) / (2.0 * a);

                if (discriminant < 0.0)
                    return -1.0;
                if (isValidHit(t1, oAxis, dAxis))
                    return t1;
                if (isValidHit(t2, oAxis, dAxis))
                    return t2;
                return -1.0;
            }

            [[nodiscard]] std::shared_ptr<IMaterial> getMaterial() const override
            {
                return _material;
            }

            [[nodiscard]] std::string getName() const override
            {
                return _name;
            }

            [[nodiscard]] Math::Vector3D getPosition() const override
            {
                return {apex.X, apex.Y, apex.Z};
            }

            [[nodiscard]] ColorRGB getColor() const override
            {
                return _color;
            }
    };
}

#endif /* !MYPROJECT_CONE_HPP */
