#pragma once

#include <MCGE/Essentials/Objects/Headers/Vector2.hpp>
#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <string>
#include <vector>



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


        Tile();
        Tile(int _id);
        ~Tile();
        // set texture id of a tile
        void setId(int _id);
    };


    class Tileset : public gm::GameObject
    {
    private:
    public:

        // tile size default 16x16 pixels
        gm::Vector2 tile_size = gm::Vector2{16,16};
        // all possible textures for a tiles
        // std::vector<sf::Texture> textures;
        std::vector<std::string> textures;

        // all used tiles where id != 0
        std::map<std::string, gm::Tile> tiles;

        std::vector<int> missing_textures;

        std::map<std::string, int> tex_names;


        Tileset();
        ~Tileset();
        int getTexIdByName(std::string _name);



        // set tile's id
        void setTile(gm::Vector2 _pos, int _id);

        void setTile(int _x, int _y, int _id);

        void setTile(int _x, int _y, std::string _tex_name);
        gm::Tile getTile(int _x, int _y);
        gm::Tile getTile(gm::Vector2 _vec);

        // updates information about tiles
        void update();
        // set id for tiles between _a and _b
        void fill(Vector2 _a, Vector2 _b, int _id);
        // load textures
        void loadTiles(std::string _path, std::string _new_tex_name);



        void loadMap(std::string _path);
        void saveTileset(std::string _path);
        void renderTiles();
        void showTextures();
};
}