#pragma once

#include <MCGE/Libraries.hpp>
#include <MCGE/objects/Vector2.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <MCGE/engine.hpp>

#include <MCGE/Functions.hpp>
#include <MCGE/Essentials/Variables.hpp>

#ifndef TILESET_HPP
#define TILESET_HPP

namespace gm {
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
        Tile(int _id) {
            id = _id;
        }
        ~Tile() {
        }
        // set texture id of a tile
        void setId(int _id) {
            id = _id;
        }
    };


    class Tileset : public gm::GameObject
    {
    private:
    public:

        // tile size default 16x16 pixels
        Vector2 tile_size = Vector2{16,16};
        // all possible textures for a tiles
        // std::vector<sf::Texture> textures;
        std::vector<std::string> textures;

        // all used tiles where id != 0
        std::map<std::string, Tile> tiles;

        std::vector<int> missing_textures;

        std::map<std::string, int> tex_names;


        Tileset() {
            if (node_type_id == 0) {
                node_type_id = 3;
            }
            
        }
        ~Tileset() {
        }

        int getTexIdByName(std::string _name) {
            
        }



        // set tile's id
        void setTile(Vector2 _pos, int _id) {
            std::string code = std::to_string((int) _pos.x) + ":" + std::to_string((int) _pos.y);
            if (_id < textures.size()+1) {
                if (_id > 0) {
                    tiles[code].setId(_id);
                    tiles[code].sprite.setPosition( _pos.x * tile_size.x, _pos.y * tile_size.y);
                    // tiles[code].sprite.setPosition(100,100);
                } else if (_id == 0) {
                    tiles.erase(code);
                }
            } else {
                tiles[code].setId(_id);
                tiles[code].sprite.setPosition( _pos.x * tile_size.x, _pos.y * tile_size.y);
                if (std::find(missing_textures.begin(), missing_textures.end(), _id) == missing_textures.end()) {
                    missing_textures.push_back(_id);
                    // std::cout<<name + " (Tileset): There's no texture for that ID - "<<_id<<std::endl;
                    this->log("There's no texture for that ID - " + std::to_string(_id));
                // std::cout<<name + " (Tileset): Nie znaleziono tekstury dla ID - "<<_id<<std::endl;
                }
            }
            update();
        }

        void setTile(int _x, int _y, int _id) {
            setTile(Vector2{_x,_y}, _id);
        }

        void setTile(int _x, int _y, std::string _tex_name) {
            // std::cout<<_tex_name<<" --> "<<tex_names[_tex_name]<<std::endl;
            setTile(Vector2{_x,_y}, tex_names[_tex_name]);
        }

        Tile getTile(int _x, int _y) {
            std::string _code = std::to_string(_x)+":"+std::to_string(_y);
            for (const auto &[code, tile]: tiles) {
                if (_code == code) {
                    return tile;
                }
            }
            return Tile(0);
        }
        Tile getTile(Vector2 _vec) {
            return getTile(_vec.x, _vec.y);
        }

        // updates information about tiles
        void update() {
            for ( const auto &[key, value]: tiles ) {
                // std::cout << key << '\n';
                if (tiles[key].id-1 < textures.size()) {
                    // tiles[key].sprite.setTexture(textures[tiles[key].id-1]);
                    // tiles[key].sprite.setTexture(TEXTURES["TILE_" + std::to_string(tiles[key].id-1)]);
                    tiles[key].sprite.setTexture(TEXTURES[textures[tiles[key].id-1]]);
                    // tiles[key].sprite.setOrigin(0,value.sprite.getTexture()->getSize().y);
                } else {
                    tiles[key].sprite.setScale(tile_size.x / 2, tile_size.y / 2);
                    tiles[key].sprite.setTexture(TEXTURES["MISSING_TEXTURE"]);
                }
                // for (const auto& entry : textures) {
                
                // }
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
        void loadTiles(std::string _path = "assets/sprites/tileset/", std::string _new_tex_name = "TILE_") {
            this->log("Loading Textures...");
            int i = -1;
            for (const auto & entry : std::filesystem::directory_iterator(_path)) {
                i++;
                this->log(gm::loadTexture(_new_tex_name + std::to_string(i), entry.path()));
                // sf::Texture texture;
                // texture.loadFromFile(entry.path());
                // textures.push_back(texture);
                textures.push_back(_new_tex_name + std::to_string(i));
                tex_names[entry.path().filename().string()] = textures.size();
                // std::cout<<"SIZE : "<<textures.size()<<std::endl;
            }
            this->log("Finished loading Textures");
            auto _size = TEXTURES[textures[0]].getSize();
            tile_size = gm::Vector2{_size.x,_size.y};
            // for (auto const &[name, id]: tex_names) {
                // std::cout<<name<<" --> "<<id<<std::endl;
            // }
            // for every file load new texture "TILE_X" X = number of texture
            // 
        }



        void loadMap(std::string _path = "assets/tilesets/test.tileset") {
            this->log("Started loading tilemap file");
            std::string line;
            std::ifstream savefile(_path);
            std::vector<std::string> _tiles;
            std::string num;
            while (getline(savefile, line)) {
                std::stringstream _param(line);
                std::vector<int> _tile;
                while (getline(_param, num, ' ')) {
                    _tile.push_back(std::stoi(num));
                }
                setTile(_tile[0], _tile[1], _tile[2]);
            }
            this->log("Loaded tilemap file (" + _path + ")");
        }
        void saveTileset(std::string _path = "assets/tilesets/test.tileset") {
            this->log("Saving tilemap file");
            std::ofstream _savefile(_path);
            for ( const auto &[key, value]: tiles ) {
                std::stringstream _code(key);
                std::string _pos;
                while(std::getline(_code, _pos, ':')) {
                    _savefile << _pos << ' ';
                }
                _savefile<<value.id<<std::endl;
            }
            _savefile.close();
            this->log("Saved tilemap file (" + _path + ")");
        }
        void renderTiles() {
            for ( const auto &[key, value]: tiles ) {
                WINDOW.draw(tiles[key].sprite);
            }
        }
        void showTextures() {
            this->log("Loaded Textures:");
            for (int t = 0; t < textures.size(); t++) {
                std::cout<<"ID: "<<t+1<<" Texture: "<<textures[t]<<std::endl;
            }
        }
};

}

#endif