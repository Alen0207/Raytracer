/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PrimitiveFactory
*/

#ifndef PRIMITIVEFACTORY_HPP_
    #define PRIMITIVEFACTORY_HPP_

#include <functional>
#include <memory>
#include <string>
#include <exception>
#include <unordered_map>
#include "interfaces/IPrimitive.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Parsing.hpp"
#include "Plane.hpp"

namespace RayTracer
{
    class PrimitiveFactory
    {
        public:
            using PrimFunc = std::function<std::unique_ptr<IPrimitive>()>;

            PrimitiveFactory()
            {
                _makers["sphere"] = []() {
                    return std::make_unique<Sphere>();
                };
                _makers["cone"] = []() {
                    return std::make_unique<Cone>();
                };
                _makers["plane"] = []() {
                    return std::make_unique<Plane>();
                };
            }
            ~PrimitiveFactory() = default;

            [[nodiscard]] std::unique_ptr<IPrimitive>
                createPrimitive(const std::string &type) const
            {
                auto it = _makers.find(type);
                if (it == _makers.end())
                    throw Error("Error: Unknown primitive type: '" + type + "'");
                return it->second();
            }

            [[nodiscard]] std::unique_ptr<IPrimitive>
                createPrimitive(const SPHERE &data) const
            {
                auto [pos, radius, color] = data;
                ColorRGB normalized = {
                    std::get<0>(color) / 255.0,
                    std::get<1>(color) / 255.0,
                    std::get<2>(color) / 255.0
                };
                return std::make_unique<Sphere>(pos, radius, normalized);
            }

            [[nodiscard]] std::unique_ptr<IPrimitive>
                createPrimitive(const PLANE &data) const
            {
                auto [axis, pos, color] = data;
                Math::Vector3D vec = {0, 0, 0};
                ColorRGB normalized = {
                    std::get<0>(color) / 255.0,
                    std::get<1>(color) / 255.0,
                    std::get<2>(color) / 255.0
                };
                if (axis == "X")
                    vec.X = pos;
                else if (axis == "Y")
                    vec.Y = pos;
                else if (axis == "Z")
                    vec.Z = pos;
                return std::make_unique<Plane>(vec, normalized);
            }

            [[nodiscard]] std::unique_ptr<IPrimitive>
                createPrimitive(const CONE &data) const
            {
                ColorRGB normalized = {
                    std::get<0>(data.color) / 255.0,
                    std::get<1>(data.color) / 255.0,
                    std::get<2>(data.color) / 255.0
                };
                return std::make_unique<Cone>(data.apex, data.halfAngle * M_PI / 180.0, normalized, data.axis);
            }

            void registerType(const std::string &name, PrimFunc func)
            {
                _makers[name] = func;
            }

            class Error : public std::exception
            {
                public:
                    explicit Error(const std::string &msg) : _msg(msg) {}
                    const char *what() const noexcept override { return _msg.c_str(); }
                private:
                    std::string _msg;
            };

        private:
            std::unordered_map<std::string, PrimFunc> _makers;
    };
}

#endif /* !PRIMITIVEFACTORY_HPP_ */
