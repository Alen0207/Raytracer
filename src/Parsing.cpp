/*
** EPITECH PROJECT, 2026
** MyProject
** File description:
** Parsing
*/

#include "../include/Parsing.hpp"
#include <libconfig.h++>

Parsing::Parsing(const std::string &file)
{
    _filename = file;
}

Parsing::~Parsing() = default;

static double lookupDouble(const libconfig::Setting &s, const char *key, double def = 0.0)
{
    double d = def;
    int i = static_cast<int>(def);

    if (s.lookupValue(key, d))
        return d;
    if (s.lookupValue(key, i))
        return static_cast<double>(i);
    return def;
}

void Parsing::parse()
{
    _cfg.readFile(_filename.c_str());
    const libconfig::Setting &root = _cfg.getRoot();

    if (root.exists("camera"))
        ParseCamera(root["camera"]);
    if (root.exists("primitives")) {
        const libconfig::Setting &prim = root["primitives"];
        if (prim.exists("spheres"))
            ParseSpheres(prim["spheres"]);
        if (prim.exists("planes"))
            ParsePlanes(prim["planes"]);
        if (prim.exists("cones"))
            ParseCones(prim["cones"]);
    }
    if (root.exists("lights"))
        ParceLights(root["lights"]);
}

void Parsing::ParseSpheres(const libconfig::Setting &spheres)
{
    for (int i = 0; i < spheres.getLength(); i++) {
        const libconfig::Setting &s = spheres[i];
        const libconfig::Setting &color = s["color"];
        double x = lookupDouble(s, "x");
        double y = lookupDouble(s, "y");
        double z = lookupDouble(s, "z");
        double r = lookupDouble(s, "r");
        double red = lookupDouble(color, "r");
        double grn = lookupDouble(color, "g");
        double blu = lookupDouble(color, "b");
        _sphere.push_back({Math::Point3D(x, y, z), r, {red, grn, blu}});
    }
}

void Parsing::ParseCones(const libconfig::Setting &cones)
{
    for (int i = 0; i < cones.getLength(); i++) {
        const libconfig::Setting &c = cones[i];
        const libconfig::Setting &color = c["color"];
        CONE cone;
        std::string axis = "Z";

        c.lookupValue("axis", axis);
        cone.axis = axis;
        cone.apex = Math::Point3D(
            lookupDouble(c, "x"),
            lookupDouble(c, "y"),
            lookupDouble(c, "z")
        );
        cone.halfAngle = lookupDouble(c, "angle");
        cone.color = {
            lookupDouble(color, "r"),
            lookupDouble(color, "g"),
            lookupDouble(color, "b")
        };
        _cones.push_back(cone);
    }
}

void Parsing::ParsePlanes(const libconfig::Setting &planes)
{
    double pos;
    double red;
    double grn;
    double blu;

    for (int i = 0; i < planes.getLength(); i++) {
        const libconfig::Setting &p = planes[i];
        const libconfig::Setting &color = p["color"];
        std::string axis;
        p.lookupValue("axis", axis);
        pos = lookupDouble(p, "position");
        red = lookupDouble(color, "r");
        grn = lookupDouble(color, "g");
        blu = lookupDouble(color, "b");

        _planes.push_back({axis, pos, {red, grn, blu}});
    }
}

void Parsing::ParseCamera(const libconfig::Setting &cam)
{
    double w = 800, h = 450;
    double x = 0, y = 0, z = 0;
    double xr = 0, yr = 0, zr = 0;
    double fov = 60;

    if (cam.exists("resolution")) {
        w = lookupDouble(cam["resolution"], "width",  800);
        h = lookupDouble(cam["resolution"], "height", 450);
    }
    if (cam.exists("position")) {
        x  = lookupDouble(cam["position"], "x");
        y  = lookupDouble(cam["position"], "y");
        z  = lookupDouble(cam["position"], "z");
    }
    if (cam.exists("rotation")) {
        xr = lookupDouble(cam["rotation"], "x");
        yr = lookupDouble(cam["rotation"], "y");
        zr = lookupDouble(cam["rotation"], "z");
    }
    if (cam.exists("fieldOfView"))
        fov = lookupDouble(cam, "fieldOfView", 60);
    _cam = {{w, h}, {x, y, z}, {xr, yr, zr}, fov};
}

void Parsing::ParceLights(const libconfig::Setting &light)
{
    double ambient = lookupDouble(light, "ambient");
    double diffuse = lookupDouble(light, "diffuse");
    std::vector<Math::Point3D> points;
    double px;
    double py;
    double pz;

    if (light.exists("point")) {
        const libconfig::Setting &point = light["point"];
        for (int i = 0; i < point.getLength(); i++) {
            px = lookupDouble(point[i], "x");
            py = lookupDouble(point[i], "y");
            pz = lookupDouble(point[i], "z");
            points.emplace_back(px, py, pz);
        }
    }
    _lights = {ambient, diffuse, points};
}
