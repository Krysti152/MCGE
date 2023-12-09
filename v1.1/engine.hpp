#define MCGE

#include <chrono>
#include <thread>
#include <unistd.h>
#include <functional>

#include <MCGE/objects.hpp>

#include <fstream>
#include <sstream>

using namespace std::chrono;
using namespace std;



sf::VideoMode video_mode(800,600);




namespace gm {

    ///             GAME


    class Game {
    private:
        int scr_width;
        int scr_height;
        string game_name;
        bool full_scr;
        bool is_running;
        int frame_rate;
        float delta;
        int frames;
        float time;
        vector<string> tags;
    public:
	//Path to textures folder
        string textures_path;
        string fonts_path;
        string sounds_path;
        sf::RenderWindow *window_ptr;
        vector<GameObject> objects;
        vector<vector<sf::Sprite>> layers;
        Input input;
        
        Game();
        ~Game();
	//Returns true if game is running.
        bool isRunning();
	//Returns true if game is in fullscreen.
        bool isFullScreen();

	//Returns screen width. 
        int getScreenWidth();
	//Returns screen height.
        int getScreenHeight();
	//Returns number of current frame.
        int getFrameNo();

	//Returns time between frames.
        float getDelta();

	//Sets resolution as x-width, y-height.
        void setResolution(int x, int y);
	//Sets fullscreen mode if b == true.
        void setFullScreen(bool b);
	//Sets framerate as f.
        void setFrameRate(float f);
	//Sets name of game instance.
        void setName(string name);

	//Put this before start().
        void awake();
	//Starts program.
        void start(function<void ()> upd,function<void ()> str);
    //Runs every frame.
	    void update();
    //Updates delta
        void updateDelta() {
            delta = 1000000 / frame_rate;
        }

    };
    //constructors / destructors




    Game::Game() {
        this -> scr_width = 800;
        this -> scr_height = 600;
        this -> frames = 0;
        this -> full_scr = false;
        this -> is_running = false;
        this -> frame_rate = 60;
        this -> textures_path = "assets/sprites/";
        this -> fonts_path = "assets/fonts/";
        this -> sounds_path = "assets/sounds/";
    }
    Game::~Game() {
        this -> is_running = false;
        // cout<<"Wygenerowano " << frames << " klatek.\n";
        // cout<<"Chodzilo przez "<<(float) (delta * frames) / 1000000<<" sekund.\n";
        cout<<"Shutting Down"<<endl;
    }


    //global functions




    void Game::awake() {
        string line;
        ifstream prefs_f("pref.ini");
        vector<string> settings;
        bool pref_fsc;
        int pref_scr_x;
        int pref_scr_y;
        string word;
        while (getline(prefs_f, line)) {
            if (line.find('[') == string::npos) {
                stringstream setting(line);
                while (getline(setting, word, '=')) {
                    settings.push_back(word);
                }
            }
        }
        cout<<"Preferences:"<<endl;
        for (int i = 1; i < settings.size(); i+=2) {
            cout<<settings[i-1]<<':'<<settings[i]<<endl;
            if (settings[i-1] == "fullscreen") {
                if (settings[i] == "true") {
                    full_scr = true;
                }
            }
            if (settings[i-1] == "scr_width") {
                scr_width =  stoi(settings[i]);
            }
            if (settings[i-1] == "scr_height") {
                scr_height =  stoi(settings[i]);
            }
            if (settings[i-1] == "fps") {
                frame_rate =  stoi(settings[i]);
            }
        }
        video_mode = sf::VideoMode(scr_width, scr_height);
        cout<<"----------"<<endl;

        cout<<"MeowCat Game Engine V1.1"<<endl;
        cout<<"Starting..."<<endl;
        this -> delta = 1000000 / frame_rate;
        this -> is_running = true;
    }
    void Game::start(function<void ()> upd, function<void ()> str) {


        
        

        sf::RenderWindow win(video_mode, game_name, isFullScreen() ? sf::Style::Fullscreen : sf::Style::Default);
        str();
        this -> window_ptr = &win;
        while (isRunning()) {
            while (win.isOpen())
            {
            sf::Event event;
                while (win.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        win.close();
                }
                win.clear();
                auto start = high_resolution_clock::now();
                update();
                upd();
                win.display();
                auto stop = high_resolution_clock::now();
                auto dur = duration_cast<microseconds>(stop - start);
                //if (frames < 10) {
                //    cout<<delta<<endl;
                //    cout<<dur.count()<<endl;
                //}
                if (dur.count() < delta) {
                    usleep(delta-dur.count());
                }
            }
            this -> is_running = false;
        }
    }
    void Game::update() {
        frames++;
        input.update();
        //cout<<"update "<<frames<<endl;
        //for (int i = 0; i < objects.size();i++) {
        //    this -> objects[i].update();
        //}
    }

    //setters



    void Game::setResolution(int _x, int _y) {
        if (!isRunning()) {
            this -> scr_width = _x;
            this -> scr_height = _y;

            video_mode = sf::VideoMode(_x,_y);
        } else {
            print("Game is running.");
        }
    }
    void Game::setFullScreen(bool _bool) {
        if (!isRunning()) {
        this -> full_scr = _bool;
        } else {
            print("Game is running.");
        }
    }
    void Game::setFrameRate(float _f) {
        if (!isRunning()) {
            this -> frame_rate = _f;
            delta = 1000000 / frame_rate;
        } else {
            print("Game is running.");
        }
    }
    void Game::setName(string _name) {
        if (!isRunning()) {
            this -> game_name = _name;
        } else {
            print("Game is running.");
        }
    }


    //getters



    bool Game::isFullScreen() {
        return this -> full_scr;
    }
    bool Game::isRunning() {
        return this -> is_running;
    }

    int Game::getScreenHeight() {
        return this -> scr_height;
    }
    int Game::getScreenWidth() {
        return this -> scr_width;
    }
    int Game::getFrameNo() {
        return this -> frames;
    }
    
    float Game::getDelta() {
        return this->delta/1000000;
    }

    sf::Vector2f vec_to_sf(gm::Vector2 _vec) {
        return sf::Vector2f{_vec.x,_vec.y};
    }



}
