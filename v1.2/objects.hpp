#pragma once

#include <MCGE/Libraries.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>


#include <MCGE/objects/Vector2.hpp>
#include <MCGE/objects/Vector3.hpp>
#include <MCGE/objects/Color.hpp>
#include <MCGE/objects/GUI.hpp>
#include <MCGE/objects/GameObject.hpp>
#include <MCGE/objects/Transform.hpp>
#include <MCGE/objects/Component.hpp>
#include <MCGE/objects/InputHandler.hpp>
#include <MCGE/objects/Tileset.hpp>
#include <MCGE/objects/Animator.hpp>
#include <MCGE/objects/Path.hpp>
#include <MCGE/objects/Camera.hpp>
#include <MCGE/objects/RenderBuffer.hpp>
#include <MCGE/objects/Sprite.hpp>

#include <MCGE/Functions.hpp>

#ifndef OBJECTS_HPP
#define OBJECTS_HPP



using namespace std;


namespace gm {

    void print(string __msg) {
        cout<<__msg<<endl;
    }
    void print(Vector2 __msg) {
        for (int i = 0; i<2; i++) {
            std::cout<<'['<<__msg.x<<", "<<__msg.y<<']'<<std::endl;
        }
    }

    float distance(Vector2 a, Vector2 b) {
        return (float) abs(a.x - b.x) + abs(a.y - b.y);
    }


    float vector_len(Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
    }

    Vector2 normalize(Vector2 __vec) {

        return Vector2(__vec.x/vector_len(__vec), __vec.y/vector_len(__vec));
        
    }

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
        vector<vector<Transform>> columns;
        Vector2 offset = {0,0};

        Transform transform;

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
            Vector2 off = this->offset;
            if (this->centered) {
                off = Vector2{(float)this->width / 2, (float)this->height /2};
            }
            if (!this->isometric) {
                for (int c = 0; c < this->width; c++) {
                    columns.push_back(vector<Transform>{});
                    for (int r = 0; r < this->height; r++) {
                    this->columns[c].push_back(Transform(Vector2{(float)c * this->cell_size + this->spacing * c + this->transform.position.x - off.x * (this->cell_size + this->spacing), (float)r * this->cell_size + this->spacing * r + this->transform.position.y - off.y * (this->cell_size + this->spacing)}));
                    }
                }
            }
        }
    };

}

#endif