#ifndef POTC_MENU_H
#define POTC_MENU_H

#include "../utils/trace.hpp"

#include "../gui/bitmap.hpp"
// #include "../game.hpp"

class Game;

class Menu {
    public:
        virtual void render(Bitmap* target) = 0;
        virtual void tick(Game* game, 
            bool up, bool down, 
            bool left, bool right, bool use) = 0;
        virtual ~Menu() {};
    protected:
        Menu() = default;
};

#endif // POTC_MENU_H