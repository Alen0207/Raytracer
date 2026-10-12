/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** flatColor
*/

#ifndef MYPROJECT_FLATCOLOR_HPP
    #define MYPROJECT_FLATCOLOR_HPP
    #include <string>
    #include "Color.hpp"
    #include "interfaces/IMaterial.hpp"

namespace RayTracer
{
    class flatColor : public IMaterial
    {
        public:
            flatColor() : _albedo(Color({0, 0, 0})){}
            flatColor(const ColorRGB &color) : _albedo(Color(color)){}
            flatColor(const flatColor& copy) : _albedo(copy._albedo) {}
            ~flatColor() override = default;

            [[nodiscard]] float calculateAmbient(ILight const &ray) override {return 0;};
            [[nodiscard]] float calculateNewLight(ILight const &ray) override {return 0;};
            [[nodiscard]] Color getRayNewColor() override {return _albedo;}
            void setColor(const ColorRGB &albedo) {
                _albedo = Color(albedo);
            }

        private:
            Color _albedo;
            std::string _name = "flatColor";
    };
}

#endif //MYPROJECT_FLATCOLOR_HPP
