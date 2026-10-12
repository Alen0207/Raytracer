/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Material
*/

#ifndef MYPROJECT_MATERIAL_HPP
    #define MYPROJECT_MATERIAL_HPP
    #include "ILight.hpp"
    #include "../Color.hpp"

namespace RayTracer
{
    class IMaterial
    {
        public:
            virtual ~IMaterial() = default;

            [[nodiscard]] virtual float calculateAmbient(ILight const &ray) = 0;
            [[nodiscard]] virtual float calculateNewLight(ILight const &ray) = 0;
            [[nodiscard]] virtual Color getRayNewColor() = 0;
    };
}

#endif //MYPROJECT_MATERIAL_HPP
