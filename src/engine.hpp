#ifndef POTC_ENGINE_H
#define POTC_ENGINE_H

#include "gui/screen.hpp"
#include "game.hpp"

class Engine {
    private:
        int WIDTH, HEIGHT, SCALE;
        bool running;
        Game* game;
        Screen* screen;
        bool hadFocus;
        bool hasFocus;
    public:
        Engine(Game* game) {
            WIDTH   = 160;
            HEIGHT  = 120;
            SCALE   = 4;
            running = false;
            hasFocus = false;
            hadFocus = false;

            this->game = game; 
            screen = new Screen(WIDTH, HEIGHT);
        }

        bool isRunning() { return running; }

        void start();
        void stop();
        void run();
        void tick();
        void render();
};

#endif // POTC_ENGINE_H