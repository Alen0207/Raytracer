/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#ifndef SCENEBUILDER_HPP_
    #define SCENEBUILDER_HPP_

#include "Camera.hpp"
#include "PrimitiveFactory.hpp"
#include "Parsing.hpp"
#include "interfaces/IPrimitive.hpp"
#include "interfaces/ILight.hpp"
#include <vector>
#include <memory>

namespace RayTracer
{
    struct Scene
    {
        Camera cam;
        int width = 800;
        int height = 450;
        double ambientLight = 0.4;

        std::vector<Math::Point3D> pointLights;
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        std::vector<std::unique_ptr<ILight>> lights;
    };

    class SceneBuilder
    {
        public:
            SceneBuilder() = default;
            ~SceneBuilder() = default;

            [[nodiscard]] Scene build(const std::string &configFile);
            Camera buildCamera(const CAM &camData, int &outWidth, int &outHeight);
            void buildPrimitives(Parsing &parser, Scene &scene);
            void buildLights(Parsing &parser, Scene &scene);

        private:
            PrimitiveFactory _factory;
    };
}


#endif /* !SCENEBUILDER_HPP_ */