#pragma once

#include <MCGE/Essentials/Objects/Headers/GameObject.hpp>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>




namespace gm
{
    struct animFrame
    {
        // texture of frame
        std::string tex_name;
        // duration of frame
        float duration;
        
    };

    class Animation : public gm::GameObject {
        private:
        float timer;
        public:
        // all animation frames
        std::vector<gm::animFrame> frames;
        // actually displaying frame id
        int act_frame = 0;
        // is animation playing or not
        bool is_playing = false;

        // time between the render frames
        float delta;

        // is animation looping
        bool is_loop = true;

        Animation(std::string _name);
        Animation();
        ~Animation();

        void setAllDurations(float _dur);

        // switches to next frame
        void nextFrame();

        // imports frames from directory
        // each file as next separated frame
        void importFrames(std::string _path, float _dur);


        // starts playing
        void play();

        // stops playing
        // play() will continue playing from this stopped frame
        void stop();

        // stops playing
        // resets to the first frame
        void end();
        
        // updates timer
        // should be called per game frame
        void update();
    };

    class Animator : public gm::GameObject {
        private:
        public:
            // name of actually selected animation
            std::string act_anim;
            // all animations
            std::map<std::string, gm::Animation> animations;
            // actually frame as texture
            sf::Texture *act_frame;
            std::string act_frame_name;


            Animator();
            ~Animator();
            // starts playing
            void start();
            // stops playing
            void stop();
            // updates actual animation
            void update();
            // get actually playing frame as texture
            void getFrame();
            // add new animation
            void addAnimation(gm::Animation _anim);
            // select another animation
            void changeAnimation(std::string _name);
    };
}
