#ifndef POTC_ENTITY_ENEMY_OGRE_H
#define POTC_ENTITY_ENEMY_OGRE_H

#include "enemy.hpp"
#include "../art.hpp"

class OgreEntity : public EnemyEntity {
private:
    int shootDelay = 0;
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::OGRE; }
    OgreEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 2, art.getCol(0x82A821)) {
        this->x = x;
		this->z = z;
		health = 6;
		r = 0.4;

		flying = true;
        spinSpeed = 0.05;
    }
    void tick() override;
protected:
    void hurt(double xd, double zd) override;
};

#endif // POTC_ENTITY_ENEMY_OGRE_H