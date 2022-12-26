#include "block.hpp"
#include "solid.hpp"
#include "ladder.hpp"
#include "pit.hpp"
#include "altar.hpp"
#include "vanish.hpp"
#include "chest.hpp"
#include "torch.hpp"
#include "bars.hpp"
#include "water.hpp"
#include "door.hpp"
#include "locked_door.hpp"
#include "switch.hpp"
#include "loot.hpp"
#include "win.hpp"
#include "final_unblock.hpp"
#include "pressure_plate.hpp"
#include "ice.hpp"
#include "spirit_wall.hpp"

#include "../../entities/key.hpp"
#include "../../entities/boulder.hpp"
#include "../../entities/player.hpp"

#include "../../gui/rubble.hpp"

#include "../../art.hpp"
#include "../../sound.hpp"

#include "../../utils/random.hpp"

#include <algorithm>

extern Sound sound;
static Random rnd;

LadderBlock::LadderBlock(bool down) {
    trace("BLOCK::INIT", "LADDER");
    if (down) {
        floorTex = 1;
        addSprite(new Sprite(0, 0, 0, 8 + 3, art.getCol(LADDER_COLOR)));
    } else {
        ceilTex = 1;
        addSprite(new Sprite(0, 0, 0, 8 + 4, art.getCol(LADDER_COLOR)));
    }
}

void LadderBlock::removeEntity(Entity* entity) {
    Block::removeEntity(entity);
    if (entity->type() == ENTITY::TYPE::PLAYER) {
        wait = false;
    }
}

void LadderBlock::addEntity(Entity* entity) {
    Block::addEntity(entity);

    if (!wait && entity->type() == ENTITY::TYPE::PLAYER) {
        // trace("BLOCK::LADDER", "id: " + tstr(id));
        level->switchLevel(id);
        sound.ladder->play();
    }
}

void PitBlock::addEntity(Entity *entity) {
    Block::addEntity(entity);
    if (!filled && entity->type() == ENTITY::TYPE::BOULDER) {
        entity->remove();
        filled = true;
        blocksMotion = false;
        addSprite(new Sprite(0, 0, 0, 8 + 2, 
            ((BoulderEntity*)entity)->COLOR));
        sound.thud->play();
    }
}

bool PitBlock::blocks(Entity *entity) {
    if (entity->type() == ENTITY::TYPE::BOULDER) return false;
    return blocksMotion;
}

AltarBlock::AltarBlock() {
    trace("BLOCK::INIT", "ALTAR");
    blocksMotion = true;
    sprite = new Sprite(0, 0, 0, 16 + 4, art.getCol(0xE2FFE4));
    addSprite(sprite);
}

void AltarBlock::addEntity(Entity *entity) {
    Block::addEntity(entity);
    if (!filled && (
        entity->type() == ENTITY::TYPE::GHOST 
    ||  entity->type() == ENTITY::TYPE::GHOST_BOSS)) {
        entity->remove();
        filled = true;
        blocksMotion = false;
        sprite->removed = true;

        for (int i = 0; i < 8; i++) {
            RubbleSprite* sprite = new RubbleSprite();
            sprite->color = this->sprite->color;
            addSprite(sprite);
        }

        if (entity->type() == ENTITY::TYPE::GHOST_BOSS) {
            level->addEntity(new KeyEntity(x, y));
            sound.bosskill->play();
        } else {
            sound.altar->play();
        }
    }
}

bool VanishBlock::use(Level* level, Item* item) {
    if (gone) return false;

    gone = true;
    blocksMotion = false;
    solidRender = false;
    sound.crumble->play();

    for (int i = 0; i < 32; i++) {
        RubbleSprite* sprite = new RubbleSprite();
        sprite->color = col;
        addSprite(sprite);
    }

    return true;
}

ChestBlock::ChestBlock() {
    trace("BLOCK::INIT", "CHEST");
    tex = 1;
    open = false;
    blocksMotion = true;

    chestSprite = new Sprite(0, 0, 0, 8 * 2 + 0, art.getCol(0xffff00));
	addSprite(chestSprite);
}

bool ChestBlock::use(Level* level, Item* item) {
    if (open) return false;

    chestSprite->tex++;
    open = true;

    level->getLoot(id);
    sound.treasure->play();

    return true;
}

TorchBlock::TorchBlock() {
    trace("BLOCK::INIT", "TORCH");
    torchSprite = new Sprite(0, 0, 0, 3, art.getCol(0xffff00));
	sprites.push_back(torchSprite);
}

void TorchBlock::decorate(Level* level, int x, int y) {
    Random rnd2((x + y * 1000) * 341871231);
    // Random rnd2((x + y * 1000) * 341871231);
    double r = 0.4;
    int face = 0;
    for (int i = 0; i < 1000; i++) {
        face = rnd2.nextInt(4);
        
        if (face == 0 && level->getBlock(x - 1, y)->solidRender
        ) {
        // && level->getBlock(x - 1, y)->type() != BLOCK::TYPE::VANISH) {
            torchSprite->x -= r;
            // trace("TORCH::FACE", face);
            // break;
            return;
        }
        if (face == 1 && level->getBlock(x, y - 1)->solidRender
        ) {
        //&& level->getBlock(x - 1, y)->type() != BLOCK::TYPE::VANISH) {
            torchSprite->z -= r;
            // trace("TORCH::FACE", face);
            // break;
            return;
        }
        if (face == 2 && level->getBlock(x + 1, y)->solidRender
        ) {
        //&& level->getBlock(x - 1, y)->type() != BLOCK::TYPE::VANISH) {
            torchSprite->x += r;
            // trace("TORCH::FACE", face);
            // break;
            return;
        }
        if (face == 3 && level->getBlock(x, y + 1)->solidRender
        ) {
        //&& level->getBlock(x - 1, y)->type() != BLOCK::TYPE::VANISH) {
            torchSprite->z += r;
            // trace("TORCH::FACE", face);
            // break;
            return;
        }
    }
    // trace("FACE", face);
}

void TorchBlock::tick() {
    Block::tick();
	if (rnd.nextInt(4) == 0) torchSprite->tex = 3 + rnd.nextInt(2);
}

BarsBlock::BarsBlock() {
    trace("BLOCK::INIT", "BARS");
    sprite = new Sprite(0, 0, 0, 0, 0x202020);
    addSprite(sprite);
    blocksMotion = true;
}

bool BarsBlock::use(Level *level, Item *item) {
    if (open) return false;

    if (item->type == ITEM::TYPE::CUTTERS) {
        sound.cut->play();
        sprite->tex = 1;
        open = true;
    }

    return true;
}

bool BarsBlock::blocks(Entity *entity) {
    if (open && entity->type() == ENTITY::TYPE::PLAYER) return false;
    if (open && entity->type() == ENTITY::TYPE::BULLET) return false;
    return blocksMotion;
}

void WaterBlock::tick() {
    Block::tick();
    steps--;
    if (steps <= 0) {
        floorTex = 8 + rnd.nextInt(3);
        floorCol = art.getCol(0x0000ff);
        steps = 16;
    }
}

bool WaterBlock::blocks(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::PLAYER) {
        if (((Player*)entity)->getSelectedItem()->type 
        == ITEM::TYPE::FLIPPERS) return false;
    }
    if (entity->type() == ENTITY::TYPE::BULLET) return false;
    return blocksMotion;
}

bool DoorBlock::use(Level* level, Item* item) {
    open = !open;
    if (open)
        sound.click1->play();
    else
        sound.click2->play();
    return true;
}

void DoorBlock::tick() {
    SolidBlock::tick();
		
    if (open) openness += 0.2; else openness -= 0.2;
    if (openness < 0) openness = 0;
    if (openness > 1) openness = 1;

    double openLimit = 7 / 8.0;
    if (openness < openLimit && !open && !blocksMotion) {
        if (level->containsBlockingEntity(
                x - 0.5, y - 0.5, x + 0.5, y + 0.5)) {
            openness = openLimit;
            return;
        }
    }

    blocksMotion = openness < openLimit;
}

bool DoorBlock::blocks(Entity* entity) {
    double openLimit = 7 / 8.0;
    if (openness >= openLimit && entity->type() 
    == ENTITY::TYPE::PLAYER) return blocksMotion;
    if (openness >= openLimit && entity->type() 
    == ENTITY::TYPE::BULLET) return blocksMotion;
    if (openness >= openLimit && entity->type() 
    == ENTITY::TYPE::OGRE)   return blocksMotion;
    return true;
}

bool SwitchBlock::use(Level* level, Item* item) {
    pressed = !pressed;
    if (pressed) tex = 3;
    else tex = 2;
    
    level->trigger(id, pressed);
    if (pressed)
        sound.click1->play();
    else
        sound.click2->play();

    return true;
}

LootBlock::LootBlock() {
    trace("BLOCK::INIT", "LOOT");
    sprite = new Sprite(0, 0, 0, 16 + 2, art.getCol(0xffff80));
    addSprite(sprite);
    blocksMotion = true;
}

void LootBlock::addEntity(Entity* entity) {
    Block::addEntity(entity);
    if (!taken && entity->type() == ENTITY::TYPE::PLAYER) {
        sprite->removed = true;
        taken = true;
        blocksMotion = false;
        ((Player*) entity)->loot++;
        sound.pickup->play();
        
    }
}

bool LootBlock::blocks(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::PLAYER) return false;
	return blocksMotion;
}


void WinBlock::addEntity(Entity* entity) {
    Block::addEntity(entity);
    if (entity->type() == ENTITY::TYPE::PLAYER) {
        ((Player*)entity)->win();
    }
}

bool FinalUnlockBlock::use(Level* level, Item* item) {
    if (pressed) return false;
    if (level->player->keys < 4) return false;

    sound.click1->play();
    pressed = true;
    level->trigger(id, true);

    return true;
}

void PressurePlateBlock::tick() {
    Block::tick();
    double r = 0.2;
    bool steppedOn = level->
        containsBlockingNonFlyingEntity(x - r, y - r, x + r, y + r);
    if (steppedOn != pressed) {
        pressed = steppedOn;
        if (pressed) floorTex = 3; else floorTex = 2;

        level->trigger(id, pressed);
        if (pressed)
            sound.click1->play();
        else
            sound.click2->play();
    }
}

void IceBlock::tick() {
    Block::tick();
    floorCol = art.getCol(0x8080ff);
}

double IceBlock::getWalkSpeed(Player* player) {
    if (player->getSelectedItem()->type 
    == ITEM::TYPE::SKATES) return 0.05;
	return 1.4;
}

double IceBlock::getFriction(Player* player) {
    if (player->getSelectedItem()->type 
    == ITEM::TYPE::SKATES) return 0.98;
	return 1;
}

bool IceBlock::blocks(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::PLAYER)     return false;
    if (entity->type() == ENTITY::TYPE::BULLET)     return false;
    if (entity->type() == ENTITY::TYPE::EYE_BOSS)   return false;
    if (entity->type() == ENTITY::TYPE::EYE)        return false;
    return true;
}


SpiritWallBlock::SpiritWallBlock() {
    floorTex = 7;
    ceilTex  = 7;
    blocksMotion = true;
    for (int i = 0; i < 6; i++) {
        double x = (rnd.nextDouble() - 0.5);
        double y = (rnd.nextDouble() - 0.7) * 0.3;
        double z = (rnd.nextDouble() - 0.5);
        addSprite(new Sprite(x, y, z, 
            4 * 8 + 6 + rnd.nextInt(2), art.getCol(0x202020)));
    }
}

bool SpiritWallBlock::blocks(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::BULLET) return false;
	return Block::blocks(entity);
}

bool LockedDoorBlock::use(Level* level, Item* item) {
    return false;
}

void LockedDoorBlock::trigger(bool pressed) {
    open = pressed;
}
