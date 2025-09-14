#pragma once

#include <MCGE/Libraries.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>



#include <MCGE/objects/Vector3.hpp>
#include <MCGE/objects/Color.hpp>
#include <MCGE/objects/GUI.hpp>
#include <MCGE/objects/Component.hpp>

#include <MCGE/Essentials/Objects/Headers/Path.hpp>

#include <MCGE/Essentials/Objects/Vector2.cpp>
#include <MCGE/Essentials/Objects/GameObject.cpp>
#include <MCGE/Essentials/Objects/Transform.cpp>
#include <MCGE/Essentials/Objects/InputHandler.cpp>
#include <MCGE/Essentials/Objects/Tileset.cpp>
#include <MCGE/Essentials/Objects/Animator.cpp>
#include <MCGE/Essentials/Objects/Camera.cpp>
#include <MCGE/Essentials/Objects/RenderBuffer.cpp>
#include <MCGE/Essentials/Objects/Sprite.cpp>
#include <MCGE/Essentials/Objects/CollisionShape.cpp>
#include <MCGE/Essentials/Objects/Body.cpp>
#include <MCGE/Essentials/Objects/KinematicBody.cpp>
#include <MCGE/Essentials/Objects/StaticBody.cpp>
#include <MCGE/Essentials/Objects/Timer.cpp>

#include <MCGE/Essentials/Functions.cpp>
#include <MCGE/Essentials/Objects/Structs.cpp>


#ifndef OBJECTS_HPP
#define OBJECTS_HPP



using namespace std;


namespace gm {
    ///             Renderer

    class Renderer : Component {
        public:
            Renderer();
            ~Renderer();
            Color color();
    };
    Renderer::Renderer() {

    }

    
    

    class Grid
    {
    private:
    public:
        int width;
        int height;
        std::vector<std::vector<gm::Transform>> columns;
        gm::Vector2 offset = {0,0};

        gm::Transform transform;

        int cell_size;
        int spacing;
        bool centered;
        bool isometric;

        Grid() {
        }

        Grid(int _x) {
            this->setSize(_x,_x);
        }

        Grid(int _x, int _y) {
            this->setSize(_x,_y);
        }

        ~Grid() {
        }

        void setSize(int _x, int _y) {
            this->width=_x;
            this->height=_y;
        }

        void genGrid() {
            gm::Vector2 off = this->offset;
            if (this->centered) {
                off = gm::Vector2{(float)this->width / 2, (float)this->height /2};
            }
            if (!this->isometric) {
                for (int c = 0; c < this->width; c++) {
                    columns.push_back(vector<Transform>{});
                    for (int r = 0; r < this->height; r++) {
                    this->columns[c].push_back(gm::Transform(Vector2{(float)c * this->cell_size + this->spacing * c + this->transform.position.x - off.x * (this->cell_size + this->spacing), (float)r * this->cell_size + this->spacing * r + this->transform.position.y - off.y * (this->cell_size + this->spacing)}));
                    }
                }
            }
        }
    };

}

#endif