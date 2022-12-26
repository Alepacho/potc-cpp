#ifndef POTC_MENU_GOT_LOOT_H 
#define POTC_MENU_GOT_LOOT_H

#include "menu.hpp"
#include "../entities/item.hpp"

class GotLootMenu : public Menu {
private:
    int tickDelay = 30;
    Item* item;

    void _render(Bitmap* target);
    void _tick(Game* game, 
        bool up, bool down,
        bool left, bool right, 
        bool use);
public:
    GotLootMenu() {
        trace("MENU::INIT", "GOT LOOT");
    }
    ~GotLootMenu() {
        trace("MENU::TERM", "GOT LOOT");
    }

    void render(Bitmap* target) override { _render(target); }
    void tick(Game* game, 
    bool up, bool down, bool left, bool right, 
    bool use) override {
        _tick(game, up, down, left, right, use);
    }

    GotLootMenu(Item* item) {
        this->item = item;
    }
};

#endif // POTC_LEVEL_INSTRUCTIONS_H