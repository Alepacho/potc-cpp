#ifndef POTC_ENTITIES_PLAYER_H
#define POTC_ENTITIES_PLAYER_H

#include "entity.hpp"
#include "../level/block/block.hpp"
#include "item.hpp"

class Player : public Entity {
    private:
        int deadTime = 0;
        Block* lastBlock = NULL;
    public:
        double bob, bobPhase, turnBob;
        int selectedSlot = 0;
        int itemUseTime;
        double y, ya;
        int hurtTime = 0;
	    int health = 20;
	    int keys = 0;
	    int loot = 0;
	    bool dead = false;
        int ammo = 0;
	    int potions = 0;
        bool sliding = false;
        int time;

        Item* items[8];
        const int items_length = 8;

        Player() {
            r = 0.3;
            for (int i = 0; i < items_length; i++) {
                items[i] = &ITEM::none;
            }
        }
        ENTITY::TYPE type() const override  { return ENTITY::TYPE::PLAYER; }

        void tick() override {}
        void tick(bool up, bool down, bool left, bool right, bool turnLeft, bool turnRight);
        void activate();
        bool blocks(Entity* entity, double x2, double z2, double r2) override;
        Item* getSelectedItem();
        void addLoot(Item* item);
        void hurt(Entity* enemy, int dmg);
        void collide(Entity* entity) override;
        void win();
};

#endif // POTC_ENTITIES_PLAYER_H