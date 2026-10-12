/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Color
*/


#ifndef MYPROJECT_COLOR_HPP
    #define MYPROJECT_COLOR_HPP
    #include <tuple>

namespace RayTracer
{
    using ColorRGB = std::tuple<double, double, double>;
    class Color
    {
    public:
        Color(ColorRGB color)
        {
            r = std::get<0>(color);
            g = std::get<1>(color);
            b = std::get<2>(color);
        };
        ~Color() = default;

        double r;
        double g;
        double b;
    };
}

#endif //MYPROJECT_COLOR_HPP
