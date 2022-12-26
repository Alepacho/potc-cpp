#ifndef POTC_ENTITY_BOULDER_H
#define POTC_ENTITY_BOULDER_H

#include "entity.hpp"

class BoulderEntity : public Entity {
private:
    Sprite* sprite;
    double rollDist = 0;
public:
    ENTITY::TYPE type() const override { return ENTITY::TYPE::BOULDER; }
    int COLOR;
    BoulderEntity(int x, int z);
    void tick() override;
    bool use(Entity* source, Item* item) override;
};

#endif // POTC_ENTITY_BOULDER_H