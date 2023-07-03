#ifndef POTC_MENU_TITLE_H
#define POTC_MENU_TITLE_H

#include <vector>
#include <string>

#include "menu.hpp"


class TitleMenu : public Menu {
private:
    std::vector<std::string> options;
    size_t selected;
    bool firstTick;

    void _render(Bitmap* target);
    void _tick(Game* game, 
        bool up, bool down,
        bool left, bool right, 
        bool use);
public:
    TitleMenu() {
        trace("MENU::INIT", "TITLE");
        selected = 0;
        firstTick = true;
        options = {
            "New Game", "Instructions", "About", "Exit"
        };
    }
    ~TitleMenu() {
        trace("MENU::TERM", "TITLE");
    }

    void render(Bitmap* target) override { _render(target); }
    void tick(Game* game, 
    bool up, bool down, bool left, bool right, 
    bool use) override {
        _tick(game, up, down, left, right, use);
    }
};


#endif // POTC_MENU_TITLE_H