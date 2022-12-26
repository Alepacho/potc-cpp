#ifndef POTC_ENTITY_BULLET_H
#define POTC_ENTITY_BULLET_H

#include "entity.hpp"

class Bullet : public Entity {
public:
    ENTITY::TYPE type() const override  { return ENTITY::TYPE::BULLET; }
    Entity* owner;
    Bullet(Entity* owner, double x, double z, double rot, double pow, int sprite, int col);
    void tick() override;
	bool blocks(Entity* entity, double x2, double z2, double r2) override;
protected:
    void collide(Entity* entity) override {}
};

#endif // POTC_ENTITY_BULLET_H