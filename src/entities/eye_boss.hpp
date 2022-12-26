#ifndef POTC_ENTITY_ENEMY_EYE_BOSS_H
#define POTC_ENTITY_ENEMY_EYE_BOSS_H

#include "enemy.hpp"
#include "../art.hpp"

class EyeBossEntity : public EnemyEntity {
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::EYE_BOSS; }
    EyeBossEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 4, art.getCol(0xffff00)) {
        this->x = x;
		this->z = z;
		health = 10;
        r = 0.3;
        runSpeed = 4;
        spinSpeed *= 1.5;
		flying = true;
    }
protected:
    void die() override;
};

#endif // POTC_ENTITY_ENEMY_EYE_BOSS_H