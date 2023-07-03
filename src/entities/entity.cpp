#include "entity.hpp"
#include "boulder.hpp"
#include "bullet.hpp"
#include "key.hpp"
#include "player.hpp"

#include "../level/block/block.hpp"

#include "../art.hpp"
#include "../sound.hpp"
#include "../utils/math.hpp"
#include "../utils/random.hpp"

extern Sound sound;
static Math math;

void Entity::updatePos() {
    int xTile = (int) (x + 0.5);
    int zTile = (int) (z + 0.5);
    if (xTile != xTileO || zTile != zTileO) {
        level->getBlock(xTileO, zTileO)->removeEntity(this);

        xTileO = xTile;
        zTileO = zTile;

        if (!removed) level->getBlock(xTileO, zTileO)->addEntity(this);
    }
}

void Entity::remove() {
    Block* result = level->getBlock(xTileO, zTileO);//removeEntity(this);
    if (result) {
        result->removeEntity(this);
    }
	removed = true;
}

bool Entity::blocks(Entity* entity, double x2, double z2, double r2) {
    if (entity->type() == ENTITY::TYPE::BULLET) {
        Bullet* bullet = (Bullet*)entity;
        if (bullet->owner == this) return false;
    }
    if (x + r <= x2 - r2) return false;
    if (x - r >= x2 + r2) return false;

    if (z + r <= z2 - r2) return false;
    if (z - r >= z2 + r2) return false;

    return true;
}

bool Entity::contains(double x2, double z2) {
    if (x + r <= x2) return false;
    if (x - r >= x2) return false;

    if (z + r <= z2) return false;
    if (z - r >= z2) return false;

    return true;
}

bool Entity::isInside(double x0, double z0, double x1, double z1) {
    if (x + r <= x0) return false;
    if (x - r >= x1) return false;

    if (z + r <= z0) return false;
    if (z - r >= z1) return false;

    return true;
}

void Entity::move() {
    int xSteps = (int) (math.abs(xa * 100) + 1);
    for (int i = xSteps; i > 0; i--) {
        double xxa = xa;
        if (isFree(x + xxa * i / xSteps, z)) {
            x += xxa * i / xSteps;
            break;
        } else {
            xa = 0;
        }
    }

    int zSteps = (int) (math.abs(za * 100) + 1);
    for (int i = zSteps; i > 0; i--) {
        double zza = za;
        if (isFree(x, z + zza * i / zSteps)) {
            z += zza * i / zSteps;
            break;
        } else {
            za = 0;
        }
    }
}

bool Entity::isFree(double xx, double yy) {
    int x0 = (int) (math.floor(xx + 0.5 - r));
    int x1 = (int) (math.floor(xx + 0.5 + r));
    int y0 = (int) (math.floor(yy + 0.5 - r));
    int y1 = (int) (math.floor(yy + 0.5 + r));

    if (level->getBlock(x0, y0)->blocks(this)) return false;
    if (level->getBlock(x1, y0)->blocks(this)) return false;
    if (level->getBlock(x0, y1)->blocks(this)) return false;
    if (level->getBlock(x1, y1)->blocks(this)) return false;

    int xc = (int) (math.floor(xx + 0.5));
    int zc = (int) (math.floor(yy + 0.5));

    int rr = 2;
    for (int z = zc - rr; z <= zc + rr; z++) {
        for (int x = xc - rr; x <= xc + rr; x++) {
            std::vector<Entity*> es = level->getBlock(x, z)->entities;
            for (int i = 0; i < (int)es.size(); i++) {
                Entity* e = es.at(i);
                if (e == this) continue;

                if (!e->blocks(this, this->x, this->z, r) && e->blocks(this, xx, yy, r)) {
                    e->collide(this);
                    this->collide(e);
                    return false;
                }
            }
        }
    }
    return true;
}

BoulderEntity::BoulderEntity(int x, int z) {
    trace("ENTITY::INIT", "BOULDER");
    COLOR = art.getCol(0xAFA293);
    this->x = x;
    this->z = z;
    sprite = new Sprite(0, 0, 0, 8, COLOR);
    sprites.push_back(sprite);
}

void BoulderEntity::tick() {
    rollDist += math.sqrt(xa * xa + za * za);
    sprite->tex = 8 + ((int) (rollDist * 4) & 1);

    double xao = xa;
    double zao = za;

    move();

    if (xa == 0 && xao != 0) xa = -xao * 0.3;
    if (za == 0 && zao != 0) za = -zao * 0.3;

    xa *= 0.98;
    za *= 0.98;

    if (xa * xa + za * za < 0.0001) {
        xa = za = 0;
    }
}

bool BoulderEntity::use(Entity* source, Item* item) {
    // trace("ENTITY::BOULDER", "Use: " + item->name);
    if (item->type != ITEM::TYPE::POWER_GLOVE) return false;
    sound.roll->play();

    xa += math.sin(source->rot) * 0.1;
    za += math.cos(source->rot) * 0.1;

    return true;
}


KeyEntity::KeyEntity(double x, double z) {
    trace("ENTITY::INIT", "KEY");
    COLOR = art.getCol(0x00ffff);
    this->x = x;
    this->z = z;
    y  = 0.5;
    ya = 0.025;
    sprite = new Sprite(0, 0, 0, 16 + 3, COLOR);
    sprites.push_back(sprite);
}

void KeyEntity::tick() {
    move();
    y += ya;
    if (y < 0) y = 0;
    ya -= 0.005;
    sprite->y = y;
}

void KeyEntity::collide(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::PLAYER) {
        sound.key->play();
        ((Player*)entity)->keys++;
        remove();
    }
}


Bullet::Bullet(Entity* owner, double x, double z, double rot, double pow, int sprite, int col) {
    this->r = 0.01;
    this->owner = owner;

    xa = math.sin(rot) * 0.2 * pow;
    za = math.cos(rot) * 0.2 * pow;
    this->x = x - za / 2;
    this->z = z + xa / 2;

    sprites.push_back(new Sprite(0, 0, 0, 8 * 3 + sprite, art.getCol(col)));

    flying = true;
}

void Bullet::tick() {
    double xao = xa;
    double zao = za;
    move();

    if ((xa == 0 && za == 0) || xa != xao || za != zao) {
        remove();
    }
}

bool Bullet::blocks(Entity* entity, double x2, double z2, double r2) {
    if (entity->type() == ENTITY::TYPE::BULLET) {
        return false;
    }
    if (entity == owner) return false;
    
    return Entity::blocks(entity, x2, z2, r2);
}
