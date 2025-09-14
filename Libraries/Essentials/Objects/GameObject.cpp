#pragma once

#include <MCGE/Essentials/Objects/Headers/Transform.hpp>
#include <MCGE/Essentials/Variables.hpp>

gm::GameObject::GameObject() {
    name = "GameObject";
    is_active = true;
    // init();
}

gm::GameObject::GameObject(std::string _name) {
    name = _name;
    is_active = true;
    // init();
}

gm::GameObject::~GameObject() {

}
void gm::GameObject::setActive(bool _bool) {
    this -> is_active = _bool;
}

std::string gm::GameObject::getName() {
    return std::to_string(node_id) + ":" + std::to_string(node_type_id);
}

void gm::GameObject::update() {
    // std::cout<<subclass_name<<std::endl;
    if (parent != 0) {
        gm::Transform p_transform = parent->transform;
        transform.position.x = p_transform.position.x - transform.position.x;
        transform.position.y = p_transform.position.y - transform.position.y;
        // transform.setPosition(parent->transform.getPosition());
    }
    // if (parent.id > 0) {
        
    // }
}


void gm::GameObject::log(std::string _msg) {
    std::cout<<name + " (" + std::to_string(this->node_id) + "-" + ob_types[this->node_type_id] + "): " + _msg<<std::endl;
}

void gm::GameObject::init() {
    int new_id = rand() % 10001;
    for (int i = 0; i < OBJECTS.size(); i++) {
        if (OBJECTS[i].id == new_id) {
            this->init();
            std::cout<<"Powtarza sie"<<std::endl;
            return;
        }
    }
    this->node_id = new_id;
    OBJECTS.push_back(gm::ob_data{new_id, this->node_type_id});
}