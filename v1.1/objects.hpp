#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include <filesystem>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>

//#include <MCGE/objects/GUI.hpp>

using namespace std;


namespace gm {

    //          Color

    class Color {
        private:
        public:
            int r;
            int g;
            int b;
            int a;
            Color() {
                r,g,b,a = 1;
            }
            Color(int gray) {
                r,g,b = gray;
                a = 1;
            }
    };

    //          Position

    class Vector2
    {
    private:
    public:
        float x;
        float y;







        void lookAt(Vector2 destination) {
                //6             10
            if (x > destination.x) {
                x = -x - abs(destination.x);//-4
            } else {
                x = -x + destination.x;//4
            }
            if (y > destination.y) {
                y = -y - abs(destination.y);
            } else {
                y = -y + destination.y;
            }
        }

        void normalize() {
            float __len = len(Vector2(x,y));
            x = x/__len;
            y = y/__len;
        }

        float len(Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
        }

        float distanceTo(Vector2 b) {
        return (float) abs(x - b.x) + abs(y - b.y);
        }

        void multiplyBy(float __val) {
            x,y *= __val;
        }

        



        Vector2() {
            x,y = 0;
        }
        Vector2(int n, int m) {
            x = n;
            y = m;
        }
        Vector2(float n, float m) {
            x = n;
            y = m;
        }
        ~Vector2();
    };

    Vector2::~Vector2()
    {
    }
    

    class Vector3
    {
    private:
    public:
        float x;
        float y;
        float z;

        Vector3() {
            x,y,z = 0;
        }
        Vector3(int n, int m, int o) {
            x = n;
            y = m;
            z = o;
        }
        Vector3(float n, float m, float o) {
            x = n;
            y = m;
            z = o;
        }
        ~Vector3();
    };

    Vector3::~Vector3()
    {
    }

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

    ///             Component

    class Component {
        public:
            bool enabled = true;
    };



    ///             Transform

    class Transform {
        public:
            Transform();
            Transform(Vector2 vec);

            Vector2 position = {0,0};
            float rotation;
            Vector2 scale = {0,0};
            void setPosition(Vector2 __vec);
            void setPosition(float x, float y);
            void setPosition(int x, int y);
            void addPosition(Vector2 __vec);
            Vector2 getPosition();
    };

    Transform::Transform() {
        position = Vector2(0,0);
    }

    Transform::Transform(Vector2 __vec) {
        this->setPosition(__vec);
    }
    void Transform::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    void Transform::setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void Transform::setPosition(Vector2 vec) {
        this -> position.x = vec.x;
        this -> position.y = vec.y;
    }

    Vector2 Transform::getPosition() {
        return this->position;
    }

    void Transform::addPosition(Vector2 __vec) {
        position.x += __vec.x;
        position.y += __vec.y;
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

    struct animFrame
    {
        // texture of frame
        sf::Texture texture;
        // duration of frame
        float duration;
        
    };

    class Animation {
        private:
        float timer;
        public:
        // all animation frames
        vector<animFrame> frames;
        // actually displaying frame id
        int act_frame = 0;
        // is animation playing or not
        bool is_playing = false;

        // time between the render frames
        float delta;

        // is animation looping
        bool is_loop = true;

        Animation(float _delta) {
            this->delta = _delta;
        }
        Animation() {
        }
        ~Animation() {
        }

        // switches to next frame
        void nextFrame() {
                if (this->act_frame >= this->frames.size()-1) {
                    if (this->is_loop) {
                        this->act_frame = 0;
                    } else {
                        this->stop();
                    }
                } else {
                    this->act_frame++;
                }
            }

        // imports frames from directory
        // each file as next separated frame
        void importFrames(string _path = "assets/sprites/anim/", float _dur = 1) {
            for (const auto & entry : filesystem::directory_iterator(_path)) {
                sf::Texture texture;
                texture.loadFromFile(entry.path());
                this->frames.push_back(gm::animFrame{texture,_dur});
            }
        }


        // starts playing
        void play() {
            this->is_playing = true;
        }
        // stops playing
        // play() will continue playing from this stopped frame
        void stop() {
            this->is_playing = false;
        }
        // stops playing
        // resets to the first frame
        void end() {
            this->stop();
            act_frame = 0;
        }
        
        // updates timer
        // should be called per game frame
        void update() {
                if (is_playing && frames.size() > 0) {
                    if (timer >= frames[act_frame].duration) {
                        timer = 0;
                        this->nextFrame();
                    }
                    timer += delta;
                }
            }
    };

    class Animator : Component {
        private:
        public:
            // name of actually selected animation
            string act_anim;
            // all animations
            map<string, Animation> animations;
            // actually frame as texture
            sf::Texture *act_frame;


            Animator() {
            }
            ~Animator() {

            }
            // starts playing
            void start() {
                animations[act_anim].play();
                getFrame();
            }
            // stops playing
            void stop() {
                animations[act_anim].stop();
            }
            // updates actual animation
            void update() {
                animations[act_anim].update();
                getFrame();
            }
            // get actually playing frame as texture
            void getFrame() {
                act_frame = &animations[act_anim].frames[animations[act_anim].act_frame].texture;
            }
            // add new animation
            void addAnimation(string _name,Animation _anim) {
                act_anim = _name;
                this->animations.insert({_name, _anim});
            }
            // select another animation
            void changeAnimation(string _name) {
                animations[act_anim].end();
                act_anim = _name;
                animations[act_anim].play();
            }

    };

    class Tile
    {
    private:
    public:

        // sprite
        sf::Sprite sprite;
        // texture id of a tile
        int id;

        // has collision
        bool has_collision = false;


        Tile() {
        }
        ~Tile() {
        }
        // set texture id of a tile
        void setId(int _id) {
            id = _id;
        }
    };


    class Tileset
    {
    private:
    public:

        // tile size default 16x16 pixels
        Vector2 tile_size = Vector2{16,16};
        // all possible textures for a tiles
        vector<sf::Texture> textures;

        // all used tiles where id != 0
        map<string, Tile> tiles;


        Tileset() {
        }
        ~Tileset() {
        }
        // set tile's id
        void setTile(Vector2 _pos, int _id) {
            string code = to_string((int) _pos.x) + ":" + to_string((int) _pos.y);
            if (_id > 0) {
                tiles[code].setId(_id);
                tiles[code].sprite.setPosition( _pos.x * tile_size.x, _pos.y * tile_size.y);
                // tiles[code].sprite.setPosition(100,100);
            } else if (_id == 0) {
                tiles.erase(code);
            }
            update();
        }
        // updates information about tiles
        void update() {
            for ( const auto &[key, value]: tiles ) {
                // std::cout << key << '\n';
                tiles[key].sprite.setTexture(textures[tiles[key].id-1]);
            }
        }
        // set id for tiles between _a and _b
        void fill(Vector2 _a, Vector2 _b, int _id) {
            for (int x = _a.x; x < _b.x; x++) {
                for (int y = _a.y; y < _b.y; y++) {
                    setTile(Vector2{x,y}, _id);
                }
            }
        }
        // load textures
        void loadTileset (string _path = "assets/sprites/tileset/") {
            for (const auto & entry : filesystem::directory_iterator(_path)) {
                sf::Texture texture;
                texture.loadFromFile(entry.path());
                textures.push_back(texture);
            }
        }
    };

    



    ///             GAMEOBJECT


    class GameObject {
        private:
        public:
            string name;
            bool active;
            string tag;
            Transform transform;

            GameObject() {
                this -> name = "Game Object";
                this -> active = true;
            }

            GameObject(string _name) {
                this -> name = _name;
                this -> active = true;
            }

            ~GameObject() {

            }
            void setActive(bool _bool) {
                this -> active = _bool;
            }

            void update() {

            }
            vector<Component> components;
    };

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


    class Input {
        private:
            Vector2 dir = {0,0};
            map<string, float> Axis = {
                        {"Horizontal", 0},
                        {"Vertical", 0},
                        {"Jump", 0},
                        {"Crouch", 0},
                        {"Sprint", 0},
                        {"Action", 0},
                        {"MouseLeft", 0},
                        {"MouseMiddle", 0},
                        {"MouseRight", 0}
                    };
        public:

            void update() {
                int left = 0;
                int right = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    left = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    right = 1;
                };

                int up = 0;
                int down = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    up = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    down = 1;
                };

                

                Axis["Horizontal"] = right - left;
                Axis["Vertical"] = up - down;
                Axis["Jump"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
                Axis["Crouch"] = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
                Axis["Sprint"] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
                Axis["Action"] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
                Axis["MouseLeft"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
                Axis["MouseMiddle"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
                Axis["MouseRight"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
            }
            Vector2 getNormDir() {
                return normalize(dir);
            }
            Vector2 getDir() {
                return dir;
            }
            float getAxis(string _name) {
                return Axis[_name];
            }

    };



}
