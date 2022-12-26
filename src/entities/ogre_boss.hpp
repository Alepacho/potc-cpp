#ifndef POTC_ENTITY_ENEMY_OGRE_BOSS_H
#define POTC_ENTITY_ENEMY_OGRE_BOSS_H

#include "enemy.hpp"
#include "../art.hpp"

class OgreBossEntity : public EnemyEntity {
private:
    int shootDelay, shootPhase;
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::OGRE_BOSS; }
    OgreBossEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 2, art.getCol(0xffff00)) {
        this->x = x;
		this->z = z;
		health = 10;
		r = 0.4;
		flying = true;
        spinSpeed = 0.05;
    }
    void tick() override;
protected:
    void die() override;
};

#endif // POTC_ENTITY_ENEMY_OGRE_BOSS_H