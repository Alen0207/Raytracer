/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Parsing
*/

#ifndef MYPROJECT_PARSING_HPP
    #define MYPROJECT_PARSING_HPP

#include <libconfig.h++>
#include <string>
#include <vector>
#include "Point3D.hpp"
#include "Color.hpp"

using COORD = std::tuple<double, double, double>;
using DIMENTION = std::tuple<double, double>;
using SPHERE = std::tuple<Math::Point3D, double, RayTracer::ColorRGB>;
using PLANE = std::tuple<std::string, double, RayTracer::ColorRGB>;
using CAM = std::tuple<DIMENTION, COORD, COORD, double>;
using LIGHTS = std::tuple<double, double, std::vector<Math::Point3D>>;
struct CONE
{
    Math::Point3D apex;
    double halfAngle;
    RayTracer::ColorRGB color;
    std::string axis = "Z";
};

class Parsing
{
    public:
        Parsing(const std::string &file);
        ~Parsing();

        void parse();
        void ParseSpheres(const libconfig::Setting &spheres);
        void ParsePlanes(const libconfig::Setting &planes);
        void ParseCones(const libconfig::Setting &cones);
        void ParseCamera(const libconfig::Setting &cam);
        void ParceLights(const libconfig::Setting &light);

        [[nodiscard]] const std::vector<SPHERE> &getSpheres() const { return _sphere; }
        [[nodiscard]] const std::vector<PLANE> &getPlanes() const { return _planes; }
        [[nodiscard]] const std::vector<CONE> &getCones() const { return _cones; }
        [[nodiscard]] const CAM &getCam() const { return _cam; }
        [[nodiscard]] const LIGHTS &getLights() const { return _lights; }
        [[nodiscard]] const std::vector<std::string> &getPlugins() const { return _plugins; }

    private:
        std::string _filename;
        std::vector<SPHERE> _sphere;
        std::vector<PLANE> _planes;
        std::vector<CONE> _cones;
        CAM _cam;
        LIGHTS _lights;
        std::vector<std::string> _plugins;
        libconfig::Config _cfg;
};

#endif //MYPROJECT_PARSING_HPP
