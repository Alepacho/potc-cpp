#ifndef POTC_ENTITY_KEY_H
#define POTC_ENTITY_KEY_H

#include "entity.hpp"

class KeyEntity : public Entity {
private:
    Sprite* sprite;
    double y, ya;
public:
    ENTITY::TYPE type() const override  { return ENTITY::TYPE::KEY; }
    int COLOR;
    KeyEntity(double x, double z);
    void tick() override;
    void collide(Entity* entity) override;
};

#endif // POTC_ENTITY_KEY_H