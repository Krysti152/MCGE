#pragma once

#include <MCGE/Essentials/Objects/Headers/Animator.hpp>

gm::Animation::Animation(std::string _name) {
    this->name = _name;
    if (node_type_id == 0) {
    node_type_id = 1;
}
}
gm::Animation::Animation() {
    this->name = "4N1M4T10N";
    if (node_type_id == 0) {
    node_type_id = 1;
}
}
gm::Animation::~Animation() {
}

void gm::Animation::setAllDurations(float _dur) {
    for (int i = 0; i < size(frames); i++) {
        frames[i].duration = _dur;
    }
}

// switches to next frame
void gm::Animation::nextFrame() {
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
void gm::Animation::importFrames(std::string _path = "assets/sprites/anim/", float _dur = 1) {
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
void gm::Animation::play() {
    this->is_playing = true;
}
// stops playing
// play() will continue playing from this stopped frame
void gm::Animation::stop() {
    this->is_playing = false;
}
// stops playing
// resets to the first frame
void gm::Animation::end() {
    this->stop();
    act_frame = 0;
}

// updates timer
// should be called per game frame
void gm::Animation::update() {
    if (is_playing && frames.size() > 0) {
        if (timer >= frames[act_frame].duration) {
            timer = 0;
            this->nextFrame();
        }
        timer += delta;
    }
}

gm::Animator::Animator() {
    if (node_type_id == 0) {
        node_type_id = 2;
    }
}
gm::Animator::~Animator() {

}
// starts playing
void gm::Animator::start() {
    this->log("Started playing " + act_anim);
    animations[act_anim].play();
    getFrame();
}
// stops playing
void gm::Animator::stop() {
    this->log("Stopped playing at " + std::to_string(animations[act_anim].act_frame) + " frame");
    animations[act_anim].stop();
}
// updates actual animation
void gm::Animator::update() {
    animations[act_anim].update();
    getFrame();
}
// get actually playing frame as texture
void gm::Animator::getFrame() {
    // act_frame = &animations[act_anim].frames[animations[act_anim].act_frame].texture;
    act_frame_name = animations[act_anim].frames[animations[act_anim].act_frame].tex_name;
    act_frame = &TEXTURES[act_frame_name];
}
// add new animation
void gm::Animator::addAnimation(Animation _anim) {
    this->log("Added animation " + _anim.name);
    act_anim = _anim.name;
    this->animations.insert({_anim.name, _anim});
}
// select another animation
void gm::Animator::changeAnimation(std::string _name) {
    this->log("Changed animation to " + _name);
    animations[act_anim].end();
    act_anim = _name;
    animations[act_anim].play();
}