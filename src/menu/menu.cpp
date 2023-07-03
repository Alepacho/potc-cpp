#include "../gui/bitmap.hpp"
#include "../game.hpp"

#include "title.hpp"
#include "about.hpp"
#include "instructions.hpp"
#include "pause.hpp"
#include "got_loot.hpp"
#include "lose.hpp"
#include "win.hpp"

#include "../art.hpp"

#include "../sound.hpp"
extern Sound sound;

void TitleMenu::_render(Bitmap* target) {
    target->fill(0, 0, 160, 120, 0);
    target->draw(art.logo, 0, 8, 0, 0, 160, 36, art.getCol(0xffffff));

    for (size_t i = 0; i < options.size(); i++) {
        auto msg = options[i];
        int col = 0x909090;
        if (selected == i) {
            msg = "-> " + msg;
            col = 0xffff80;
        }
        target->draw(msg, 40, 60 + i * 10, art.getCol(col));
    }
    target->draw("Copyright (C) 2011 Mojang", 1+4, 120 - 18, art.getCol(0x303030));
    target->draw("C++ port by Alepacho", 1+4, 120 - 9, art.getCol(0x303030));
}

void TitleMenu::_tick(Game *game, bool up, bool down, bool left, bool right, bool use) {
    if (firstTick) {
        firstTick = false;
        sound.altar->play();
    }
    if (up || down) sound.click2->play();
    if (up) selected--;
    if (down) selected++;
    if (selected < 0) selected = 0;
    if (selected >= options.size()) selected = options.size() - 1;
    if (use) {
        sound.click1->play();

        switch (selected) {
            case 0:
                game->setMenu(NULL);
                game->newGame();
            break;
            case 1:
                game->setMenu(new InstructionsMenu());
            break;
            case 2:
                game->setMenu(new AboutMenu());
            break;
            case 3:
                game->exitGame();
            break;
        }
    }
}

void AboutMenu::_render(Bitmap* target) {
    target->fill(0, 0, 160, 120, 0);

    std::vector<std::string> lines = {
        "Prelude of the Chambered",
        "by Markus Persson.",
        "Made Aug 2011 for the",
        "21'st Ludum Dare compo.",
        "",
        "This game is freeware,",
        "and was made from scratch",
        "in just 48 hours.",
    };
    
    for (size_t i = 0; i < lines.size(); i++) {
        target->draw(lines[i], 4, 28 + i * 8, art.getCol(0xa0a0a0));
    }

    if (tickDelay == 0)
        target->draw("-> Continue", 40, target->height - 16, art.getCol(0xffff80));
}

void AboutMenu::_tick(Game* game, 
bool up, bool down,
bool left, bool right, 
bool use) {
    if (tickDelay > 0) tickDelay--;
    else if (use) {
        sound.click1->play();
        game->setMenu(new TitleMenu());
    }
}

void InstructionsMenu::_render(Bitmap* target) {
    target->fill(0, 0, 160, 120, 0);

    target->draw("Instructions", 40, 8, art.getCol(0xffffff));

    std::vector<std::string> lines = {
        "Use W,A,S,D to move, and",
        "the arrow keys to turn.",
        "",
        "The 1-8 keys select",
        "items from the inventory",
        "",
        "Space uses items",
    };
    
    for (size_t i = 0; i < lines.size(); i++) {
        target->draw(lines[i], 4, 32 + i * 8, art.getCol(0xa0a0a0));
    }

    if (tickDelay == 0)
        target->draw("-> Continue", 40, target->height - 16, art.getCol(0xffff80));
}

void InstructionsMenu::_tick(Game* game, 
bool up, bool down,
bool left, bool right, 
bool use) {
    if (tickDelay > 0) tickDelay--;
    else if (use) {
        sound.click1->play();
        game->setMenu(new TitleMenu());
    }
}

void PauseMenu::_render(Bitmap* target) {
    target->draw(art.logo, 0, 8, 0, 0, 160, 36, art.getCol(0xffffff));

    for (size_t i = 0; i < options.size(); i++) {
        std::string msg = options[i];
        int col = 0x909090;
        if (selected == i) {
            msg = "-> " + msg;
            col = 0xffff80;
        }
        target->draw(msg, 40, 60 + i * 10, art.getCol(col));
    }
}

void PauseMenu::_tick(Game* game, 
bool up, bool down,
bool left, bool right, 
bool use) {
    if (up || down) sound.click2->play();
    if (up) selected--;
    if (down) selected++;
    if (selected < 0) selected = 0;
    if (selected >= options.size()) selected = options.size() - 1;
    if (use) {
        sound.click1->play();
        if (selected == 0) {
            game->setMenu(new TitleMenu());
        }
        if (selected == 1) {
            game->setMenu(NULL);
        }
    }
}

void GotLootMenu::_render(Bitmap* target) {
    std::string str = "You found the " + item->name + "!";
    target->scaleDraw(art.items, 3, target->width / 2 - 8 * 3, 2, item->icon * 16, 0, 16, 16, art.getCol(item->color));
    target->draw(str, (target->width - str.length() * 6) / 2 + 2, 60 - 10, art.getCol(0xffff80));

    str = item->description;
    target->draw(str, (target->width - str.length() * 6) / 2 + 2, 60, art.getCol(0xa0a0a0));

    if (tickDelay == 0) target->draw("-> Continue", 40, target->height - 40, art.getCol(0xffff80));
}

void GotLootMenu::_tick(Game* game, 
bool up, bool down,
bool left, bool right, 
bool use) {
    if (tickDelay > 0) tickDelay--;
    else if (use) {
        game->setMenu(NULL);
    }
}

void WinMenu::render(Bitmap* target) {
    target->draw(art.logo, 0, 10, 0, 65, 160, 23, art.getCol(0xffffff));

    int seconds = player->time / 60;
    int minutes = seconds / 60;
    seconds %= 60;
    std::string timeString = tstr(minutes) + ":";
    if (seconds < 10) timeString += "0";
    timeString += seconds;
    target->draw("Trinkets: " + tstr(player->loot) + "/12", 40, 45 + 10 * 0, art.getCol(0x909090));
    target->draw("Time: " + timeString, 40, 45 + 10 * 1, art.getCol(0x909090));

    if (tickDelay == 0) target->draw("-> Continue", 40, target->height - 40, art.getCol(0xffff80));
}

void WinMenu::tick(Game* game, 
bool up, bool down, 
bool left, bool right, 
bool use) {
    if (tickDelay > 0) tickDelay--; else if (use) {
        sound.click1->play();
        game->setMenu(new TitleMenu());
    }
}

void LoseMenu::render(Bitmap* target) {
    target->draw(art.logo, 0, 10, 0, 39, 160, 23, art.getCol(0xffffff));

    int seconds = player->time / 60;
    int minutes = seconds / 60;
    seconds %= 60;
    std::string timeString = tstr(minutes) + ":";
    if (seconds < 10) timeString += "0";
    timeString += seconds;
    target->draw("Trinkets: " + tstr(player->loot) + "/12", 40, 45 + 10 * 0, art.getCol(0x909090));
    target->draw("Time: " + timeString, 40, 45 + 10 * 1, art.getCol(0x909090));

    if (tickDelay == 0) target->draw("-> Continue", 40, target->height - 40, art.getCol(0xffff80));
}

void LoseMenu::tick(Game* game, 
bool up, bool down, 
bool left, bool right, 
bool use) {
    if (tickDelay > 0) tickDelay--; else if (use) {
        sound.click1->play();
        game->setMenu(new TitleMenu());
    }
}