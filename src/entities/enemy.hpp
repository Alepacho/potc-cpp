#ifndef POTC_ENTITY_ENEMY
#define POTC_ENTITY_ENEMY

#include "entity.hpp"
#include "../gui/sprite.hpp"

#include "../utils/math.hpp"

class EnemyEntity : public Entity {
public:
    ENTITY::TYPE type() const override  { return ENTITY::TYPE::ENEMY; }
    
    EnemyEntity() : Entity() {}

    EnemyEntity(double x, double z, int defaultTex, int defaultColor) : EnemyEntity() {
		this->x = x;
		this->z = z;
		this->defaultColor = defaultColor;
		this->defaultTex = defaultTex;
		sprite = new Sprite(0, 0, 0, 4 * 8, defaultColor);
		sprites.push_back(sprite);
		r = 0.3;
	}

    void tick() override;
    bool use(Entity* source, Item* item) override;
protected:
    Sprite* sprite;
    double rot, rota;
    int defaultTex, defaultColor;
    int hurtTime = 0, animTime = 0;
    int health = 3;
    double spinSpeed = 0.1, runSpeed = 1;

    virtual void hurt(double xd, double zd);
    virtual void die() {}
    void collide(Entity* entity) override;
};

#endif // POTC_ENTITY_ENEMY