#ifndef POTC_ENTITY_ENEMY_BAT_H
#define POTC_ENTITY_ENEMY_BAT_H

#include "enemy.hpp"
#include "../art.hpp"

class BatEntity : public EnemyEntity {
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::BAT; }
    BatEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8, art.getCol(0x82666E)) {
        this->x = x;
		this->z = z;
		health = 2;
		r = 0.3;

		flying = true;
    }
};

#endif // POTC_ENTITY_ENEMY_BAT_H