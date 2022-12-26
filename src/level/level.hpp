#ifndef POTC_LEVEL_H
#define POTC_LEVEL_H

#include <vector>
#include <string>
#include <unordered_map>

#include "../gui/bitmap.hpp"
#include "../utils/trace.hpp"

class Block;
class Entity;
class Game;
class Player;
class Item;

namespace LEVEL {
    enum ID {
        IDK,
        OVERWORLD,
        DUNGEON
    };
}

class Level {
private:
    Block* solidWall;
    static Level* byName(std::string name);
public:
    Bitmap* levelBitmap = NULL;
    std::vector<Block*> blocks;
    int width, height;
    int xSpawn, ySpawn;
    std::vector<Entity*> entities;
    std::string name;
    Player* player;

    Level();
    virtual ~Level();

    Bitmap* getLevelBitmap() { return levelBitmap; }

    virtual void init(Game* game, std::string name, Bitmap* bitmap);
    void addEntity(Entity* e);
    void removeEntityImmediately(Player* player);

    static void clear();
    static Level* loadLevel(Game* game, std::string name);
	bool containsBlockingEntity(double x0, double y0, double x1, double y1);
	bool containsBlockingNonFlyingEntity(double x0, double y0, double x1, double y1);
    void tick();
    virtual void trigger(int id, bool pressed);
    virtual void switchLevel(int id) {}
    void findSpawn(int id);
    virtual void getLoot(int id);
    void win();
    void lose();
    void showLootScreen(Item* item);

    virtual void decorateBlock(int x, int y, Block* block, int col);
    virtual Block* getBlock(int x, int y, int col);
    Block* getBlock(int x, int y);
protected:
    int wallCol = 0xB3CEE2, floorCol = 0x9CA09B, ceilCol = 0x9CA09B;
    int wallTex = 0, floorTex = 0, ceilTex = 0;
    Game* game;
};

#endif // POTC_LEVEL_H