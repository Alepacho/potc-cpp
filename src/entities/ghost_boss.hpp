#ifndef POTC_ENTITY_ENEMY_GHOST_BOSS_H
#define POTC_ENTITY_ENEMY_GHOST_BOSS_H

#include "enemy.hpp"
#include "../art.hpp"

class GhostBossEntity : public EnemyEntity {
private:
    double rotatePos = 0;
    int shootDelay = 0;
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::GHOST_BOSS; }
    GhostBossEntity(double x, double z) :
    EnemyEntity(x, z, 4 * 8 + 6, art.getCol(0xffff00)) {
        this->x = x;
		this->z = z;
		health = 10;
		flying = true;
    }
    void tick() override;
protected:
    void hurt(double xd, double zd) override {}
    void move() override {
        x += xa;
		z += za;
    }
};

#endif // POTC_ENTITY_ENEMY_GHOST_BOSS_H