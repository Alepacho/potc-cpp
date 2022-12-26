#ifndef POTC_LEVEL_ABOUT_H 
#define POTC_LEVEL_ABOUT_H

#include "menu.hpp"

class AboutMenu : public Menu {
private:
    int tickDelay = 30;

    void _render(Bitmap* target);
    void _tick(Game* game, 
        bool up, bool down,
        bool left, bool right, 
        bool use);
public:
    AboutMenu() {
        trace("MENU::INIT", "ABOUT");
    }
    ~AboutMenu() {
        trace("MENU::TERM", "ABOUT");
    }

    void render(Bitmap* target) override { _render(target); }
    void tick(Game* game, 
    bool up, bool down, bool left, bool right, 
    bool use) override {
        _tick(game, up, down, left, right, use);
    }
};

#endif // POTC_LEVEL_ABOUT_H