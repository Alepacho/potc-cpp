#ifndef POTC_ENTITY_H
#define POTC_ENTITY_H

#include "../gui/sprite.hpp"
#include "../level/level.hpp"
#include "item.hpp"

#include "../utils/random.hpp"
#include "../utils/trace.hpp"

namespace ENTITY {
    enum TYPE {
        BOULDER,
        BULLET,
        KEY,
        ENEMY,
        BAT_BOSS,
        BAT,
        OGRE_BOSS,
        OGRE,
        EYE_BOSS,
        EYE,
        GHOST_BOSS,
        GHOST,
        PLAYER,
        ITEM
    };
};

class Entity {
    private:
        bool removed = false;
    public:
        double x, z, rot;
        double xa, za, rota;
        double r = 0.4;

        Level* level;
        int xTileO = -1, zTileO = -1;
        bool flying = false;

        std::vector<Sprite*> sprites;
        
        Entity() {
            r = 0.4;
            xTileO = zTileO = -1;
        }
        virtual ~Entity() {};

        virtual ENTITY::TYPE type() const = 0;

        void updatePos(); // final;
        bool isRemoved() { return removed; }
        void remove();
        virtual bool blocks(Entity* entity, double x2, double z2, double r2);
        bool contains(double x2, double z2);
        bool isInside(double x0, double z0, double x1, double z1);
        virtual bool use(Entity* source, Item* item) { return false; }
        virtual void tick() {};

        static std::string getName(ENTITY::TYPE type) {
            switch (type) {
                case ENTITY::TYPE::BOULDER:     return "BOULDER";
                case ENTITY::TYPE::BULLET:      return "BULLET";
                case ENTITY::TYPE::KEY:         return "KEY";
                case ENTITY::TYPE::ENEMY:       return "ENEMY";
                case ENTITY::TYPE::BAT_BOSS:    return "BAT_BOSS";
                case ENTITY::TYPE::BAT:         return "BAT";
                case ENTITY::TYPE::OGRE_BOSS:   return "OGRE_BOSS";
                case ENTITY::TYPE::OGRE:        return "OGRE";
                case ENTITY::TYPE::EYE_BOSS:    return "EYE_BOSS";
                case ENTITY::TYPE::EYE:         return "EYE";
                case ENTITY::TYPE::GHOST_BOSS:  return "GHOST_BOSS";
                case ENTITY::TYPE::GHOST:       return "GHOST";
                case ENTITY::TYPE::PLAYER:      return "PLAYER";
                case ENTITY::TYPE::ITEM:        return "ITEM";
                default: return "UNKNOWN";
            }
        }
        bool isFree(double xx, double yy);
    protected:
        // static Random random; // final;
        virtual void move();
        virtual void collide(Entity* entity) {};
};

#endif // POTC_ENTITY_H