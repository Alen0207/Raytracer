/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** MaterialFactory
*/

#ifndef MATERIALSFACTORY_HPP_
    #define MATERIALSFACTORY_HPP_

    #include <functional>
    #include <memory>
    #include <unordered_map>
    #include <string>
    #include <utility>
    #include "flatColor.hpp"
    #include "interfaces/IMaterial.hpp"

namespace RayTracer
{
    class MaterialsFactory
    {
    private:
        using materialFuncs = std::function<std::shared_ptr<IMaterial>()>;
        std::unordered_map<std::string, materialFuncs> _materials;

    public:
        MaterialsFactory()
        {
            _materials["flatColor"] = []() -> std::shared_ptr<IMaterial> {
                return std::make_shared<flatColor>();
            };
        }

        [[nodiscard]] std::shared_ptr<IMaterial>
            createMaterial(const std::string &type) const
        {
            const auto it = _materials.find(type);
            if (it == _materials.end())
                throw Error("Unknown material type: '" + type + "'");
            return it->second();
        }

        [[nodiscard]] bool hasType(const std::string &type) const
        {
            return _materials.count(type) > 0;
        }

        class Error : public std::exception
        {
        public:
            explicit Error(std::string msg) : _msg(std::move(msg)) {}
            [[nodiscard]] const char *what() const noexcept override
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
        };
    };
}

#endif /* !MATERIALSFACTORY_HPP_ */
