#ifndef POTC_MENU_INSTRUCTIONS_H 
#define POTC_MENU_INSTRUCTIONS_H

#include "menu.hpp"

class InstructionsMenu : public Menu {
private:
    int tickDelay = 30;

    void _render(Bitmap* target);
    void _tick(Game* game, 
        bool up, bool down,
        bool left, bool right, 
        bool use);
public:
    InstructionsMenu() {
        trace("MENU::INIT", "INSTRUCTIONS");
    }
    ~InstructionsMenu() {
        trace("MENU::TERM", "INSTRUCTIONS");
    }

    void render(Bitmap* target) override { _render(target); }
    void tick(Game* game, 
    bool up, bool down, bool left, bool right, 
    bool use) override {
        _tick(game, up, down, left, right, use);
    }
};

#endif // POTC_LEVEL_INSTRUCTIONS_H