#ifndef POTC_ENTITY_ENEMY_EYE_H
#define POTC_ENTITY_ENEMY_EYE_H

#include "enemy.hpp"
#include "../art.hpp"

class EyeEntity : public EnemyEntity {
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::EYE; }
    EyeEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 4, art.getCol(0x84ECFF)) {
        this->x = x;
		this->z = z;
		health = 4;
		r = 0.3;
        runSpeed = 2;
        spinSpeed *= 1.5;
		flying = true;
    }
};

#endif // POTC_ENTITY_ENEMY_EYE_H