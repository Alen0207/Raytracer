/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Camera
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include <cmath>

namespace RayTracer
{
    class Camera
    {
        public:
            Camera() { build(); }
            Camera(Math::Point3D position, Math::Point3D target, double fovDeg,
                double ratio) : _position(position), _target(target),
                _fovDeg(fovDeg), _ratio(ratio)
            { build(); }

            ~Camera() = default;

            [[nodiscard]] Ray ray(double u, double v) const
            {
                Math::Point3D pixel = {
                    _screenCenter.X + (u - 0.5) * _viewportW * _right.X
                        + (v - 0.5) * _viewportH * _up.X,
                    _screenCenter.Y + (u - 0.5) * _viewportW * _right.Y
                        + (v - 0.5) * _viewportH * _up.Y,
                    _screenCenter.Z + (u - 0.5) * _viewportW * _right.Z
                        + (v - 0.5) * _viewportH * _up.Z
                };
                Math::Vector3D dir = {
                    pixel.X - _position.X,
                    pixel.Y - _position.Y,
                    pixel.Z - _position.Z
                };
                return Ray{_position, dir};
            }

            static Math::Vector3D normalize(Math::Vector3D v)
            {
                double len = std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);

                if (len == 0.0)
                    return {0, 0, 1};
                return {v.X / len, v.Y / len, v.Z / len};
            }

            static Math::Vector3D cross(Math::Vector3D a, Math::Vector3D b)
            {
                return {
                    a.Y * b.Z - a.Z * b.Y,
                    a.Z * b.X - a.X * b.Z,
                    a.X * b.Y - a.Y * b.X
                };
            }

            void build()
            {
                double dot;
                double halfH;

                _forward = normalize({
                    _target.X - _position.X,
                    _target.Y - _position.Y,
                    _target.Z - _position.Z
                });
                Math::Vector3D worldUp = {0, 0, 1};
                dot = _forward.X * worldUp.X + _forward.Y * worldUp.Y
                    + _forward.Z * worldUp.Z;
                if (std::abs(dot) > 0.999)
                    worldUp = {0, 1, 0};
                _right = normalize(cross(_forward, worldUp));
                _up = normalize(cross(_right, _forward));
                halfH = std::tan((_fovDeg * M_PI / 180.0) / 2.0);
                _viewportH = 2.0 * halfH;
                _viewportW = _viewportH * _ratio;
                _screenCenter = {
                    _position.X + _forward.X,
                    _position.Y + _forward.Y,
                    _position.Z + _forward.Z
                };
            }

        private:
            Math::Point3D _position = {0, 0, 0};
            Math::Point3D _target = {0, 1, 0};
            double _fovDeg = 72.0;
            double _ratio = 16.0 / 9.0;
            double _viewportH = 1.0;
            double _viewportW = 1.0;
            Math::Point3D _screenCenter;
            Math::Vector3D _forward;
            Math::Vector3D _right;
            Math::Vector3D _up;
    };
}

#endif /* CAMERA_HPP */
