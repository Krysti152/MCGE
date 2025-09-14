#pragma once

#include <MCGE/objects/Component.hpp>

#include <iostream>
#include <vector>
#include <MCGE/Essentials/Objects/Headers/Transform.hpp>
#include <MCGE/Essentials/Objects/Structs.cpp>

namespace gm {

class GameObject {
        private:
        public:
            std::string name;
            bool is_active;
            std::string tag;
            std::vector<std::string> tags;
            gm::Transform transform;
            std::string subclass_name;
            int node_type_id;
            gm::GameObject* parent;
            // gm::ob_data parent;
            int node_id;

            void init();

            GameObject();

            GameObject(std::string _name);

            ~GameObject();
            void setActive(bool _bool);

            std::string getName();

            void update();

            void log(std::string _msg);
            
};

}