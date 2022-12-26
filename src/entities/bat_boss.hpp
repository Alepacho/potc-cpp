#ifndef POTC_ENTITY_ENEMY_BAT_BOSS_H
#define POTC_ENTITY_ENEMY_BAT_BOSS_H

#include "enemy.hpp"
#include "../art.hpp"

class BatBossEntity : public EnemyEntity {
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::BAT_BOSS; }
    BatBossEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8, art.getCol(0xffff00)) {
        this->x = x;
		this->z = z;
		health = 5;
		r = 0.3;
		flying = true;
    }
    void tick() override;
protected:
    void die() override;
};

#endif // POTC_ENTITY_ENEMY_BAT_BOSS_H