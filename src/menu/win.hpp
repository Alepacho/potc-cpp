#ifndef POTC_MENU_WIN_H
#define POTC_MENU_WIN_H

#include "menu.hpp"
#include "../entities/player.hpp"

class WinMenu : public Menu {
private:
    int tickDelay = 30;
    Player* player;
public:
    WinMenu(Player* player) {
		this->player = player;
	}
    void render(Bitmap* target) override;
    void tick(Game* game, 
        bool up, bool down, 
        bool left, bool right, 
        bool use) override;
};

#endif // POTC_MENU_WIN_H