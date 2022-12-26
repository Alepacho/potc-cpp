#include "game.hpp"

#include "menu/menu.hpp"
#include "menu/title.hpp"
#include "menu/pause.hpp"
#include "menu/win.hpp"
#include "menu/lose.hpp"

#include "level/block/ladder.hpp"

#include "utils/input.hpp"
#include "utils/math.hpp"

static Math math;

Game::Game() {
    level = NULL;
    player = NULL;
    exit = false;

    setMenu(new TitleMenu());
}

Game::~Game() {
    if (menu)   delete menu;
    if (level)  delete level;
    if (player) delete player;
}

void Game::newGame() {
    level->clear();
    level = level->loadLevel(this, "start");

    player = new Player();
    player->level = level;
    level->player = player;
    player->x = level->xSpawn;
    player->z = level->ySpawn;
    level->addEntity(player);
    player->rot = math.PI + 0.4;
}

void Game::exitGame() {
    exit = true;
}

void Game::switchLevel(std::string name, int id) {
    pauseTime = 30;
    level->removeEntityImmediately(player);
    level = level->loadLevel(this, name);
    level->findSpawn(id);
    player->x = level->xSpawn;
    player->z = level->ySpawn;

    LadderBlock* block = (LadderBlock*)level->getBlock(level->xSpawn, level->ySpawn);
    block->wait = true;

    player->x += math.sin(player->rot) * 0.2;
    player->z += math.cos(player->rot) * 0.2;
    level->addEntity(player);
}

void Game::tick(bool* keys) {
    if (pauseTime > 0) {
        pauseTime--; return;
    }

    time++;

    bool strafe = keys[KEY_EVENT::CONTROL] || keys[KEY_EVENT::ALT] || keys[KEY_EVENT::ALT_GRAPH] || keys[KEY_EVENT::SHIFT];

    bool lk = keys[KEY_EVENT::LEFT]  || keys[KEY_EVENT::NUMPAD4];
    bool rk = keys[KEY_EVENT::RIGHT] || keys[KEY_EVENT::NUMPAD6];

    bool up     = keys[KEY_EVENT::W] || keys[KEY_EVENT::UP]   || keys[KEY_EVENT::NUMPAD8];
    bool down   = keys[KEY_EVENT::S] || keys[KEY_EVENT::DOWN] || keys[KEY_EVENT::NUMPAD2];
    bool left   = keys[KEY_EVENT::A] || (strafe && lk);
    bool right  = keys[KEY_EVENT::D] || (strafe && rk);

    bool turnLeft  = keys[KEY_EVENT::Q] || (!strafe && lk);
    bool turnRight = keys[KEY_EVENT::E] || (!strafe && rk);

    bool use = keys[KEY_EVENT::SPACE] || keys[KEY_EVENT::ENTER];

    for (int i = 0; i < 8; i++) {
        if (keys[KEY_EVENT::K1 + i]) {
            keys[KEY_EVENT::K1 + i] = false;
            player->selectedSlot = i;
            player->itemUseTime  = 0;
        }
    }

    if (keys[KEY_EVENT::ESCAPE]) {
        keys[KEY_EVENT::ESCAPE] = false;
        if (!menu) {
            setMenu(new PauseMenu());
        }
    }

    if (use) {
        keys[KEY_EVENT::SPACE] = false;
        keys[KEY_EVENT::ENTER] = false;
    }

    if (menu) {
        keys[KEY_EVENT::W] = keys[KEY_EVENT::UP]   = keys[KEY_EVENT::NUMPAD8] = false;
        keys[KEY_EVENT::S] = keys[KEY_EVENT::DOWN] = keys[KEY_EVENT::NUMPAD2] = false;
        keys[KEY_EVENT::A] = false;
        keys[KEY_EVENT::D] = false;

        menu->tick(this, up, down, left, right, use);
    } else {
        player->tick(up, down, left, right, turnLeft, turnRight);
        if (use) {
            player->activate();
        }
        level->tick();
    }
}

void Game::getLoot(Item* item) {
    player->addLoot(item);
}

void Game::win(Player* player) {
    setMenu(new WinMenu(player));
}

void Game::setMenu(Menu* menu) {
    this->menu = menu;
}

void Game::lose(Player* player) {
    setMenu(new LoseMenu(player));
}