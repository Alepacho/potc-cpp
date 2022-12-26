#ifndef POTC_LEVEL_BLOCK_H
#define POTC_LEVEL_BLOCK_H

#include "../../utils/random.hpp"
#include "../../utils/trace.hpp"

#include "../../entities/entity.hpp"
#include "../../gui/sprite.hpp"

#include <vector>
#include <string>

namespace BLOCK {
    enum TYPE {
        BLOCK,
        LADDER,
        SOLID,
        CHEST,
        ALTAR,
        BARS,
        DOOR,
        FINAL_UNBLOCK,
        ICE,
        LOCKED_DOOR,
        LOOT,
        PIT,
        PRESSURE_PLATE,
        SPIRIT_WALL,
        SWITCH,
        TORCH,
        VANISH,
        WATER,
        WIN
    };
}


class Block {
public:
    bool blocksMotion = false;
    bool solidRender  = false;
    std::vector<std::string> messages;
    // static Block* solidWall;

    std::vector<Sprite*> sprites;
    std::vector<Entity*> entities; // list of entities on the block

    int tex = -1, col = -1;
    int floorCol = -1, ceilCol = -1;
    int floorTex = -1, ceilTex = -1;
    Level* level;
    int x, y;
    int id;

    Block() {};
    virtual ~Block() {}
    virtual BLOCK::TYPE type() const { return BLOCK::TYPE::BLOCK; };

    virtual void addSprite(Sprite* sprite) { sprites.push_back(sprite); }
    virtual bool use(Level* level, Item* item) { return false; }
    virtual void tick() {
        for (int i = 0; i < sprites.size(); i++) {
            Sprite* sprite = sprites.at(i);
            sprite->tick();
            if (sprite->removed) {
                sprites.erase(sprites.begin() + i);
                i--;
            }
        }
    }
    virtual void removeEntity(Entity* entity) {
        // trace("ENTITY::REMOVE", "" + entity->getName(entity->type()));// + " to " + hex(id));
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }
    virtual void addEntity(Entity* entity) {
        
        // trace("ENTITY::ADD", "" + entity->getName(entity->type()));// + " to " + hex(id));
        entities.push_back(entity);
    }
    virtual bool blocks(Entity* entity) { return blocksMotion; }
    virtual void decorate(Level* level, int x, int y) {}
    virtual double getFloorHeight(Entity* e) { return 0; }
    virtual double getWalkSpeed(Player* player) { return 1; }
    virtual double getFriction(Player* player) { return 0.6; }
    virtual void trigger(bool pressed) {}

    static std::string getName(BLOCK::TYPE type) {
        switch (type) {
            case BLOCK::TYPE::BLOCK:            return "BLOCK";
            case BLOCK::TYPE::LADDER:           return "LADDER";
            case BLOCK::TYPE::SOLID:            return "SOLID";
            case BLOCK::TYPE::CHEST:            return "CHEST";
            case BLOCK::TYPE::ALTAR:            return "ALTAR";
            case BLOCK::TYPE::BARS:             return "BARS";
            case BLOCK::TYPE::DOOR:             return "DOOR";
            case BLOCK::TYPE::FINAL_UNBLOCK:    return "FINAL_UNBLOCK";
            case BLOCK::TYPE::ICE:              return "ICE";
            case BLOCK::TYPE::LOCKED_DOOR:      return "LOCKED_DOOR";
            case BLOCK::TYPE::LOOT:             return "LOOT";
            case BLOCK::TYPE::PIT:              return "PIT";
            case BLOCK::TYPE::PRESSURE_PLATE:   return "PRESSURE_PLATE";
            case BLOCK::TYPE::SPIRIT_WALL:      return "SPIRIT_WALL";
            case BLOCK::TYPE::SWITCH:           return "SWITCH";
            case BLOCK::TYPE::TORCH:            return "TORCH";
            case BLOCK::TYPE::VANISH:           return "VANISH";
            case BLOCK::TYPE::WATER:            return "WATER";
            case BLOCK::TYPE::WIN:              return "WIN";
            default: return "UNKNOWN";
        }
    }
protected:
    // static Random random;
    // Block() = default;
};

// #include "solid_block.hpp"

#endif // POTC_LEVEL_BLOCK_H