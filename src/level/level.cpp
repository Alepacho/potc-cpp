#include "level.hpp"
#include "start.hpp"
#include "dungeon.hpp"
#include "overworld.hpp"
#include "temple.hpp"
#include "ice.hpp"
#include "crypt.hpp"

#include <algorithm>

#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/boulder.hpp"
#include "../entities/bat.hpp"
#include "../entities/bat_boss.hpp"
#include "../entities/ogre.hpp"
#include "../entities/ogre_boss.hpp"
#include "../entities/eye.hpp"
#include "../entities/eye_boss.hpp"
#include "../entities/ghost.hpp"
#include "../entities/ghost_boss.hpp"

#include "../game.hpp"
#include "../art.hpp"
#include "../utils/math.hpp"

#include "../menu/got_loot.hpp"

#include "block/block.hpp"
#include "block/solid.hpp"
#include "block/ladder.hpp"
#include "block/pit.hpp"
#include "block/altar.hpp"
#include "block/vanish.hpp"
#include "block/chest.hpp"
#include "block/torch.hpp"
#include "block/bars.hpp"
#include "block/water.hpp"
#include "block/door.hpp"
#include "block/switch.hpp"
#include "block/loot.hpp"
#include "block/pressure_plate.hpp"
#include "block/locked_door.hpp"
#include "block/ice.hpp"
#include "block/win.hpp"
#include "block/final_unblock.hpp"
#include "block/spirit_wall.hpp"

static std::unordered_map<std::string, Level*> loaded;
static Math math;

bool isEntity(int col) {
    switch (col) {
        case 0xAA5500:
        case 0xff0000:
        case 0xff0001:
        case 0xff0002:
        case 0xff0003:
        case 0xff0004:
        case 0xff0005:
        case 0xff0006:
        case 0xff0007:
            return true;
        break;
        default:
            return false;
    }
}

bool isBlock(int col) {
    switch (col) {
        case 0x93FF9B:
        case 0x009300:
        case 0xFFFFFF:
        case 0x00FFFF:
        case 0xFFFF64:
        case 0x0000FF:
        case 0xFF3A02:
        case 0x4C4C4C:
        case 0xFF66FF:
        case 0x9E009E:
        case 0xC1C14D:
        case 0xC6C6C6:
        case 0x00FFA7:
        case 0x009380:
        case 0xff0005:
        case 0x3F3F60:
        case 0xC6C697:
        case 0xFFBA02:
        case 0x749327:
        case 0x1A2108:
        case 0x00C2A7:
        case 0x000056:
            return true;
        break;
        default:
            return false;
    }
}

Level::Level() {
    solidWall = new SolidBlock();
}

Level::~Level() {
    delete solidWall;
    delete levelBitmap;

    for (size_t i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }
}

void Level::init(Game* game, std::string name, Bitmap* bitmap) {
    trace("LEVEL::INIT", "Init level named '" + name + "'");
    this->game = game;
    player = game->player;

    solidWall->col = art.getCol(wallCol);
	solidWall->tex = art.getCol(wallTex);

    levelBitmap = bitmap;
    int w = levelBitmap->width;
    int h = levelBitmap->height;
    int* pixels = levelBitmap->pixels;
    width = w; height = h;

    for (size_t i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }

    blocks.clear(); blocks.resize(width * height);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int col = pixels[x + y * w] & 0xffffff;
            int id = 255 - ((pixels[x + y * w] >> 24) & 0xff);

            Block* block = getBlock(x, y, col);
            block->id = id;
            // trace("id", hex(id) + " = 255 - ((" + hex(pixels[x + y * w] >> 24) + ") & 0xff)");

            if (block->tex      == -1) block->tex       = wallTex;
            if (block->floorTex == -1) block->floorTex  = floorTex;
            if (block->ceilTex  == -1) block->ceilTex   = ceilTex;
            if (block->col      == -1) block->col       = art.getCol(wallCol);
            if (block->floorCol == -1) block->floorCol  = art.getCol(floorCol);
            if (block->ceilCol  == -1) block->ceilCol   = art.getCol(ceilCol);

            blocks[x + y * w] = block;
            block->level = this;
            block->x = x;
            block->y = y;
        }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int col = pixels[x + y * w] & 0xffffff;
            decorateBlock(x, y, blocks[x + y * w], col);
        }
    }
}

void Level::addEntity(Entity* e) {
    entities.push_back(e);
    e->level = this;
    e->updatePos();
}

void Level::removeEntityImmediately(Player* player) {
    entities.erase(std::remove(entities.begin(), entities.end(), player), entities.end());
    Block* block = getBlock(player->xTileO, player->zTileO);
    if (block) {
        block->removeEntity(player);
    }
}

void Level::clear() {
    loaded.clear();
}

Level* Level::loadLevel(Game* game, std::string name) {
    auto l = loaded.find(name);
    if (l != loaded.end()) {
        trace("LEVEL::INFO", "Found loaded level: " + name);
        return loaded[name];
    }

    try {
        Bitmap* bitmap = art.loadLevel("res/level/" + name + ".png");
        if (bitmap == NULL) throw("Unable to load '" + name + "' level!");

        Level* level = Level::byName(name);
        level->init(game, name, bitmap);
        loaded.insert({name, level});

        return level;
    } catch (std::exception e) {
        trace("LEVEL::LOAD", e.what());
    }

    return NULL;
}

Level* Level::byName(std::string name) {
    if (name == "start")        return new StartLevel();
    if (name == "overworld")    return new OverworldLevel();
    if (name == "dungeon")      return new DungeonLevel();
    if (name == "crypt")        return new CryptLevel();
    if (name == "ice")          return new IceLevel();
    if (name == "temple")       return new TempleLevel();
    return NULL;
}

bool Level::containsBlockingEntity(double x0, double y0, double x1, double y1) {
    int xc = (int) (math.floor((x1 + x0) / 2));
    int zc = (int) (math.floor((y1 + y0) / 2));
    int rr = 2;
    for (int z = zc - rr; z <= zc + rr; z++) {
        for (int x = xc - rr; x <= xc + rr; x++) {
            std::vector<Entity*> es = getBlock(x, z)->entities;
            for (size_t i = 0; i < es.size(); i++) {
                Entity* e = es.at(i);
                if (e->isInside(x0, y0, x1, y1)) return true;
            }
        }
    }
    return false;
}

bool Level::containsBlockingNonFlyingEntity(double x0, double y0, double x1, double y1) {
    int xc = (int) (math.floor((x1 + x0) / 2));
    int zc = (int) (math.floor((y1 + y0) / 2));
    int rr = 2;
    for (int z = zc - rr; z <= zc + rr; z++) {
        for (int x = xc - rr; x <= xc + rr; x++) {
            std::vector<Entity*> es = getBlock(x, z)->entities;
            for (size_t i = 0; i < es.size(); i++) {
                Entity* e = es.at(i);
                if (!e->flying && e->isInside(x0, y0, x1, y1)) return true;
            }
        }
    }
    return false;
}

void Level::tick() {
    for (size_t i = 0; i < entities.size(); i++) {
        Entity* e = entities.at(i);
        e->tick();
        e->updatePos();
        if (e->isRemoved()) {
            entities.erase(entities.begin() + i);
            i--;
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            blocks[x + y * width]->tick();
        }
    }
}

void Level::trigger(int id, bool pressed) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Block* b = blocks[x + y * width];
            if (b->id == id) {
                b->trigger(pressed);
            }
        }
    }
}

void Level::findSpawn(int id) {
    trace("LEVEL::SPAWN", "Find id " + tstr(id));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Block* b = blocks[x + y * width];
            if (b->id == id) {
                if (b->type() == BLOCK::TYPE::LADDER) {
                    trace("LEVEL::INFO", "Found spawn: " + std::to_string(x) + ", " + std::to_string(y));
                    xSpawn = x;
                    ySpawn = y;
                }
            }
        }
    }
}

void Level::getLoot(int id) {
    if (id == 20) game->getLoot(&ITEM::pistol);
	if (id == 21) game->getLoot(&ITEM::potion);
}

void Level::win() {
    game->win(player);
}

void Level::lose() {
    game->lose(player);
}

void Level::showLootScreen(Item* item) {
    game->setMenu(new GotLootMenu(item));
}

void Level::decorateBlock(int x, int y, Block* block, int col) {
    bool found = false;

    block->decorate(this, x, y);
    if (col == 0xFFFF00) {
        xSpawn = x;
        ySpawn = y;
        found = true;
    }
    if (col == 0xAA5500) { found = true; addEntity(new BoulderEntity(x, y)); }
    if (col == 0xff0000) { found = true; addEntity(new BatEntity(x, y)); }
    if (col == 0xff0001) { found = true; addEntity(new BatBossEntity(x, y)); }
    if (col == 0xff0002) { found = true; addEntity(new OgreEntity(x, y)); }
    if (col == 0xff0003) { found = true; addEntity(new OgreBossEntity(x, y)); }
    if (col == 0xff0004) { found = true; addEntity(new EyeEntity(x, y)); }
    if (col == 0xff0005) { found = true; addEntity(new EyeBossEntity(x, y)); }
    if (col == 0xff0006) { found = true; addEntity(new GhostEntity(x, y)); }
    if (col == 0xff0007) { found = true; addEntity(new GhostBossEntity(x, y)); }
    if (col == 0x1A2108 || col == 0xff0007) {
        block->floorTex = 7;
        block->ceilTex  = 7;
        found = true;
    }

    if (col == 0xC6C6C6) { found = true; block->col = art.getCol(0xa0a0a0); }
    if (col == 0xC6C697) { found = true; block->col = art.getCol(0xa0a0a0); }
    if (col == 0x653A00) {
        block->floorCol = art.getCol(0xB56600);
        block->floorTex = 3 * 8 + 1;
        found = true;
    }

    if (col == 0x93FF9B) {
        block->col = art.getCol(0x2AAF33);
        block->tex = 8;
        found = true;
    }

    if (!found && col > 0) {
        if (isEntity(col)) trace("LEVEL::DECORATE", "WARINING: Can't find '" + hex(col) + "' entity!");
        else if (!isBlock(col)) trace("LEVEL::DECORATE", "WARINING: Unknown '" + hex(col) + "' block!");
    }
}

Block* Level::getBlock(int x, int y, int col) {
    if (col == 0x93FF9B) return new SolidBlock();
    if (col == 0x009300) return new PitBlock();
    if (col == 0xFFFFFF) return new SolidBlock();
    if (col == 0x00FFFF) return new VanishBlock();
    if (col == 0xFFFF64) return new ChestBlock();
    if (col == 0x0000FF) return new WaterBlock();
    if (col == 0xFF3A02) return new TorchBlock();
    if (col == 0x4C4C4C) return new BarsBlock();
    if (col == 0xFF66FF) return new LadderBlock(false);
    if (col == 0x9E009E) return new LadderBlock(true);
    if (col == 0xC1C14D) return new LootBlock();
    if (col == 0xC6C6C6) return new DoorBlock();
    if (col == 0x00FFA7) return new SwitchBlock();
    if (col == 0x009380) return new PressurePlateBlock();
    if (col == 0xff0005) return new IceBlock();
    if (col == 0x3F3F60) return new IceBlock();
    if (col == 0xC6C697) return new LockedDoorBlock();
    if (col == 0xFFBA02) return new AltarBlock();
    if (col == 0x749327) return new SpiritWallBlock();
    if (col == 0x1A2108) return new Block();
    if (col == 0x00C2A7) return new FinalUnlockBlock();
    if (col == 0x000056) return new WinBlock();
    if (col > 0 && isBlock(col)) {
        trace("LEVEL::BLOCK", "WARINING: Can't find '" + hex(col) + "' block!");
    }
    return new Block();
}

Block* Level::getBlock(int x, int y) {
    Block* result = solidWall;
    
    if (x < 0 || y < 0 || x >= width || y >= height) {
			return result;
    }

    result = blocks[x + y * width];
    // if (result->type() != BLOCK::TYPE::BLOCK) {
    //     trace("TEST", result->getName(result->type()) + ": " + tstr(x) + ", " + tstr(y)
    //      + ", " + tstr(width) + ", " + tstr(height));
    // }
    
	return blocks[x + y * width];
}

void StartLevel::switchLevel(int id) {
    trace("LEVEL::START", "Switch to id: " + tstr(id));
    if (id == 1) game->switchLevel("overworld", 1);
    if (id == 2) game->switchLevel("dungeon", 1);
}

void DungeonLevel::init(Game* game, std::string name, Bitmap* bitmap) {
    Level::init(game, name, bitmap);
    Level::trigger(6, true);
    Level::trigger(7, true);
}

void DungeonLevel::switchLevel(int id) {
    trace("LEVEL::DUNGEON", "Switch to id: " + tstr(id));
    if (id == 1) game->switchLevel("start", 2);
}

void DungeonLevel::getLoot(int id) {
    Level::getLoot(id);
    if (id == 1) game->getLoot(&ITEM::powerGlove);
}

void DungeonLevel::trigger(int id, bool pressed) {
    Level::trigger(id, pressed);
    if (id == 5) Level::trigger(6, !pressed);
    if (id == 4) Level::trigger(7, !pressed);
}


void OverworldLevel::switchLevel(int id) {
    if (id == 1) game->switchLevel("start", 1);
    if (id == 2) game->switchLevel("crypt", 1);
    if (id == 3) game->switchLevel("temple", 1);
    if (id == 5) game->switchLevel("ice", 1);
}

void OverworldLevel::getLoot(int id) {
    Level::getLoot(id);
	if (id == 1) game->getLoot(&ITEM::cutters);
}
