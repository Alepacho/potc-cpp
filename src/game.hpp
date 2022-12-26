#ifndef POTC_GAME_H
#define POTC_GAME_H

#include "menu/menu.hpp"

#include "level/level.hpp"
#include "entities/item.hpp"
#include "entities/player.hpp"

class Game {
public:
    int time, pauseTime;
    Level* level;
    Player* player;
    Menu *menu;
    bool exit;
    
    Game();
    ~Game();

    void newGame();
    void exitGame();
    void switchLevel(std::string name, int id);
    void tick(bool* keys);
    void getLoot(Item* item);
    void win(Player* player);
    void setMenu(Menu* menu);
    void lose(Player* player);
};

#endif // POTC_GAME_H