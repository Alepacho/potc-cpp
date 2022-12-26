#include "screen.hpp"

#include "../art.hpp"
#include "../utils/math.hpp"
#include "../utils/random.hpp"

static Math math;
int focus_tick = 0;

void Screen::render(Game *game, bool hasFocus) {
    if (!game->level) {
        fill(0, 0, width, height, 0);
    } else {
        bool itemUsed = game->player->itemUseTime > 0;
        Item* item = game->player->items[game->player->selectedSlot];

        if (game->pauseTime > 0) {
            fill(0, 0, width, height, 0);
            std::vector<std::string> messages = { "Entering " + game->level->name, };
            for (int y = 0; y < messages.size(); y++) {
                draw(messages[y], (width - messages[y].length() * 6) / 2, (viewport->height - messages.size() * 8) / 2 + y * 8 + 1, 0x111111);
                draw(messages[y], (width - messages[y].length() * 6) / 2, (viewport->height - messages.size() * 8) / 2 + y * 8, 0x555544);
            }
        } else {
            viewport->render(game);
            viewport->postProcess(game->level);

            Block* block = game->level->getBlock((int) (game->player->x + 0.5), (int) (game->player->z + 0.5));
            if (block->messages.size() > 0 && hasFocus) {
                for (int y = 0; y < block->messages.size(); y++) {
                    viewport->draw(block->messages[y], (width - block->messages[y].length() * 6) / 2,
                        (viewport->height - block->messages.size() * 8) / 2 + y * 8 + 1, 0x111111);
                    viewport->draw(block->messages[y], (width - block->messages[y].length() * 6) / 2,
                        (viewport->height - block->messages.size() * 8) / 2 + y * 8, 0x555544);
                }
            }

            draw(viewport, 0, 0);
            int xx = (int) (game->player->turnBob * 32);
            int yy = (int) (math.sin(game->player->bobPhase * 0.4) * 1 * game->player->bob + game->player->bob * 2);

            if (itemUsed) xx = yy = 0;
            xx += width / 2;
            yy += height - PANEL_HEIGHT - 15 * 3;
            if (item->type != ITEM::TYPE::NONE) {
                scaleDraw(art.items, 3, xx, yy, 16 * item->icon + 1, 16 + 1 + (itemUsed ? 16 : 0), 15, 15, art.getCol(item->color));
            }

            if (game->player->hurtTime > 0 || game->player->dead) {
                double offs = 1.5 - game->player->hurtTime / 30.0;
                Random rnd(111);
                if (game->player->dead) offs = 0.5;
                for (int i = 0; i < length; i++) {
                    double xp = ((i % width) - viewport->width  / 2.0) / width * 2;
                    double yp = (((double)i / width) - viewport->height / 2.0) / viewport->height * 2;

                    if (rnd.nextDouble() + offs < math.sqrt(xp * xp + yp * yp))
                        pixels[i] = (rnd.nextInt(5) / 4) * 0x550000;
                }
            }
        }

        draw(art.panel, 0, height - PANEL_HEIGHT, 0, 0, width, PANEL_HEIGHT, art.getCol(0x707070));

        draw("^", 3, height - 26 + 0, 0x00ffff);
        draw(std::to_string(game->player->keys) + "/4", 10, height - 26 + 0, 0xffffff);
        draw("%", 3, height - 26 + 8, 0xffff00);
        draw(std::to_string(game->player->loot), 10, height - 26 + 8, 0xffffff);
        draw("$", 3, height - 26 + 16, 0xff0000);
        draw(std::to_string(game->player->health), 10, height - 26 + 16, 0xffffff);

        for (int i = 0; i < 8; i++) {
            Item* slotItem = game->player->items[i];
            if (slotItem->type != ITEM::TYPE::NONE) {
                draw(art.items, 30 + i * 16, height - PANEL_HEIGHT + 2, slotItem->icon * 16, 0, 16, 16, art.getCol(slotItem->color));
                if (slotItem->type == ITEM::TYPE::PISTOL) {
                    std::string str = std::to_string(game->player->ammo);
                    draw(str, 30 + i * 16 + 17 - str.length() * 6, height - PANEL_HEIGHT + 1 + 10, 0x555555);
                }
                if (slotItem->type == ITEM::TYPE::POTION) {
                    std::string str = std::to_string(game->player->potions);
                    draw(str, 30 + i * 16 + 17 - str.length() * 6, height - PANEL_HEIGHT + 1 + 10, 0x555555);
                }
            }
        }

        draw(art.items, 30 + game->player->selectedSlot * 16, height - PANEL_HEIGHT + 2, 0, 48, 17, 17, art.getCol(0xffffff));
        draw(item->name, 26 + (8 * 16 - item->name.length() * 4) / 2, height - 9, 0xffffff);


        if (game->level->levelBitmap) {
            // draw(game->level->getLevelBitmap(), 0, 0);
        }
    }

    if (game->menu != NULL) {
        for (int i = 0; i < width * height; i++) {
            pixels[i] = (pixels[i] & 0xfcfcfc) >> 2;
        }			
        game->menu->render(this);
    }

    if (!hasFocus) {
        focus_tick++;
        for (int i = 0; i < length; i++) {
            pixels[i] = (pixels[i] & 0xfcfcfc) >> 2;
        }
        if (focus_tick / 60 % 2 != 0) {
            std::string msg = "Click to focus!";
            draw(msg, (width - msg.length() * 6) / 2, height / 3 + 4, 0xffffff);
        }
    }
}