#ifndef POTC_ENTITY_ENEMY_GHOST_H
#define POTC_ENTITY_ENEMY_GHOST_H

#include "enemy.hpp"
#include "../art.hpp"

class GhostEntity : public EnemyEntity {
private:
    double rotatePos = 0;
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::GHOST; }
    GhostEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 6, art.getCol(0xffffff)) {
        this->x = x;
		this->z = z;
		health = 4;
		r = 0.3;
		flying = true;
    }
    void tick() override;
protected:
    void hurt(double xd, double zd) override {};
    void move() override {
		x += xa;
		z += za;
	}
};

#endif // POTC_ENTITY_ENEMY_GHOST_H