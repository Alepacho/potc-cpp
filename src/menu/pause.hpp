#ifndef POTC_MENU_PAUSE_H
#define POTC_MENU_PAUSE_H

#include "menu.hpp"

#include <vector>
#include <string>

class PauseMenu : public Menu {
private:
    std::vector<std::string> options;
    size_t selected;

    void _render(Bitmap* target);
    void _tick(Game* game, 
        bool up, bool down,
        bool left, bool right, 
        bool use);
public:
    PauseMenu() {
        trace("MENU::INIT", "PAUSE");
        options = { "Abort game", "Continue" };
        selected = 1;
    }
    ~PauseMenu() {
        trace("MENU::TERM", "PAUSE");
    }

    void render(Bitmap* target) override { _render(target); }
    void tick(Game* game, 
    bool up, bool down, bool left, bool right, 
    bool use) override {
        _tick(game, up, down, left, right, use);
    }
};

#endif // POTC_MENU_PAUSE_H