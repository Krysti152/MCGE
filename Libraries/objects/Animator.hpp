#pragma once

#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP
#include <MCGE/engine.hpp>
#include <MCGE/Libraries.hpp>
#include <MCGE/objects/GameObject.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>




namespace gm
{
    struct animFrame
    {
        // texture of frame
        // sf::Texture texture;
        std::string tex_name;
        // duration of frame
        float duration;
        
    };

    class Animation : public GameObject{
        private:
        float timer;
        public:
        // all animation frames
        std::vector<animFrame> frames;
        // actually displaying frame id
        int act_frame = 0;
        // is animation playing or not
        bool is_playing = false;

        // time between the render frames
        float delta;

        // is animation looping
        bool is_loop = true;

        Animation(std::string _name) {
            this->name = _name;
            if (node_type_id == 0) {
            node_type_id = 1;
        }
        }
        Animation() {
            this->name = "4N1M4T10N";
            if (node_type_id == 0) {
            node_type_id = 1;
        }
        }
        ~Animation() {
        }

        void setAllDurations(float _dur) {
            for (int i = 0; i < size(frames); i++) {
                frames[i].duration = _dur;
            }
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
        void importFrames(std::string _path = "assets/sprites/anim/", float _dur = 1) {
            for (const auto & entry : std::filesystem::directory_iterator(_path)) {
                // sf::Texture texture;
                // texture.loadFromFile(entry.path());
                // this->frames.push_back(gm::animFrame{texture,_dur});
                std::string tex_name = name + "_ANIM_" + std::to_string(frames.size());
                this->log(gm::loadTexture(tex_name, entry.path().string()));
                this->frames.push_back(gm::animFrame{tex_name});
                // this->log("Imported frame(" + entry.path().string() + ")");
            }
            this->log("Loaded frames");

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

    class Animator : public GameObject {
        private:
        public:
            // name of actually selected animation
            std::string act_anim;
            // all animations
            std::map<std::string, Animation> animations;
            // actually frame as texture
            sf::Texture *act_frame;
            std::string act_frame_name;


            Animator() {
                if (node_type_id == 0) {
                    node_type_id = 2;
                }
            }
            ~Animator() {

            }
            // starts playing
            void start() {
                this->log("Started playing " + act_anim);
                animations[act_anim].play();
                getFrame();
            }
            // stops playing
            void stop() {
                this->log("Stopped playing at " + std::to_string(animations[act_anim].act_frame) + " frame");
                animations[act_anim].stop();
            }
            // updates actual animation
            void update() {
                animations[act_anim].update();
                getFrame();
            }
            // get actually playing frame as texture
            void getFrame() {
                // act_frame = &animations[act_anim].frames[animations[act_anim].act_frame].texture;
                act_frame_name = animations[act_anim].frames[animations[act_anim].act_frame].tex_name;
                act_frame = &TEXTURES[act_frame_name];
            }
            // add new animation
            void addAnimation(Animation _anim) {
                this->log("Added animation " + _anim.name);
                act_anim = _anim.name;
                this->animations.insert({_anim.name, _anim});
            }
            // select another animation
            void changeAnimation(std::string _name) {
                this->log("Changed animation to " + _name);
                animations[act_anim].end();
                act_anim = _name;
                animations[act_anim].play();
            }

};

}

#endif