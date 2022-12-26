#ifndef POTC_MENU_LOSE_H
#define POTC_MENU_LOSE_H

#include "menu.hpp"
#include "../entities/player.hpp"

class LoseMenu : public Menu {
private:
    int tickDelay = 30;
    Player* player;
public:
    LoseMenu(Player* player) {
		this->player = player;
	}
    void render(Bitmap* target) override;
    void tick(Game* game, 
        bool up, bool down, 
        bool left, bool right, 
        bool use) override;
};

#endif // POTC_MENU_LOSE_H