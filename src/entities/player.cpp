#include "player.hpp"
#include "bullet.hpp"

#include "../sound.hpp"
#include "../utils/math.hpp"
#include "../utils/random.hpp"
extern Sound sound;
static Math math;

void Player::tick(bool up, bool down, bool left, bool right, 
bool turnLeft, bool turnRight) {
    if (dead) {
        up = down = left = right = turnLeft = turnRight = false;
        deadTime++;
        if (deadTime > 60 * 2) {
            level->lose();
        }
    } else {
        time++;
    }
    if (itemUseTime > 0) itemUseTime--;
    if (hurtTime > 0) hurtTime--;

	Block* onBlock = level->getBlock((int) (x + 0.5), (int) (z + 0.5));
    double fh = onBlock->getFloorHeight(this);
    if (onBlock->type() == BLOCK::TYPE::WATER 
    && !(lastBlock->type() == BLOCK::TYPE::WATER)) {
        sound.splash->play();
    }
    lastBlock = onBlock;

    if (dead) fh = -0.6;
    if (fh > y) {
        y += (fh - y) * 0.2;
        ya = 0;
    } else {
        ya -= 0.01;
        y += ya;
        if (y < fh) {
            y = fh;
            ya = 0;
        }
    }

    double rotSpeed = 0.05;
    double walkSpeed = 0.03 * onBlock->getWalkSpeed(this);

    if (turnLeft)  rota += rotSpeed;
    if (turnRight) rota -= rotSpeed;

    double xm = 0;
    double zm = 0;
    if (up) zm--;
    if (down) zm++;
    if (left) xm--;
    if (right) xm++;
    double dd = xm * xm + zm * zm;
    if (dd > 0) dd = math.sqrt(dd); else dd = 1;
    xm /= dd;
    zm /= dd;

    bob *= 0.6;
    turnBob *= 0.8;
    turnBob += rota;
    bob += math.sqrt(xm * xm + zm * zm);
    bobPhase += math.sqrt(xm * xm + zm * zm) * onBlock->getWalkSpeed(this);
    bool wasSliding = sliding;
    sliding = false;

    if (onBlock->type() == BLOCK::TYPE::ICE
    && getSelectedItem()->type != ITEM::TYPE::SKATES) {
        if (xa * xa > za * za) {
            sliding = true;
            za = 0;
            if (xa > 0) xa = 0.08;
            else xa = -0.08;
            z += (((int) (z + 0.5)) - z) * 0.2;
        } else if (xa * xa < za * za) {
            sliding = true;
            xa = 0;
            if (za > 0) za = 0.08;
            else za = -0.08;
            x += (((int) (x + 0.5)) - x) * 0.2;
        } else {
            xa -= (xm * math.cos(rot) + zm * math.sin(rot)) * 0.1;
            za -= (zm * math.cos(rot) - xm * math.sin(rot)) * 0.1;
        }

        if (!wasSliding && sliding) {
            sound.slide->play();
        }
    } else {
        xa -= (xm * math.cos(rot) + zm * math.sin(rot)) * walkSpeed;
        za -= (zm * math.cos(rot) - xm * math.sin(rot)) * walkSpeed;
    }

    move();

    double friction = onBlock->getFriction(this);
    xa *= friction;
    za *= friction;
    rot += rota;
    rota *= 0.4;
}

void Player::activate() {
    Random rnd;
    if (dead) return;
    if (itemUseTime > 0) return;
    Item* item = items[selectedSlot];
    if (item->type == ITEM::TYPE::PISTOL) {
        if (ammo > 0) {
            sound.shoot->play();
            itemUseTime = 10;
            level->addEntity(new Bullet(this, x, z, rot, 1, 0, 0xffffff));
            ammo--;
        }
        return;
    }
    if (item->type == ITEM::TYPE::POTION) {
        if (potions > 0 && health < 20) {
            sound.potion->play();
            itemUseTime = 20;
            health += 5 + rnd.nextInt(6);
            if (health > 20) health = 20;
            potions--;
        }
        return;
    }
    if (item->type == ITEM::TYPE::KEY) itemUseTime = 10;
    if (item->type == ITEM::TYPE::POWER_GLOVE) itemUseTime = 10;
    if (item->type == ITEM::TYPE::CUTTERS) itemUseTime = 10;

    // trace("PLAYER", "ACTIVATE");
    double xa = (2 * math.sin(rot));
    double za = (2 * math.cos(rot));

    int rr = 3;
    int xc = (int) (x + 0.5);
    int zc = (int) (z + 0.5);
    std::vector<Entity*> possibleHits;
    for (int z = zc - rr; z <= zc + rr; z++) {
        for (int x = xc - rr; x <= xc + rr; x++) {
            std::vector<Entity*> es = level->getBlock(x, z)->entities;
            // trace(tstr(x) + ", " + tstr(y), es.size());
            for (int i = 0; i < (int)es.size(); i++) {
                Entity* e = es.at(i);
                if (e == this) continue;
                possibleHits.push_back(e);
            }
        }
    }

    int divs = 100;
    for (int i = 0; i < divs; i++) {
        double xx = x + xa * i / divs;
        double zz = z + za * i / divs;
        for (int j = 0; j < (int)possibleHits.size(); j++) {
            Entity* e = possibleHits.at(j);
            if (e->contains(xx, zz)) {
                if (e->use(this, items[selectedSlot])) {
                    // trace("PLAYER::ENTITY", "Use: " + e->getName(e->type()));
                    return;
                }
            }
        }
        int xt = (int) (xx + 0.5);
        int zt = (int) (zz + 0.5);
        if (xt != (int) (x + 0.5) || zt != (int) (z + 0.5)) {
            Block* block = level->getBlock(xt, zt);
            if (block->use(level, items[selectedSlot])) {
                // trace("PLAYER::BLOCK", "Use: " + block->getName(block->type()));
                return;
            }
            if (block->blocks(this)) return;
        }
    }
}

bool Player::blocks(Entity* entity, double x2, double z2, double r2) {
    return Entity::blocks(entity, x2, z2, r2);
}

Item* Player::getSelectedItem() {
    return items[selectedSlot];
}

void Player::addLoot(Item* item) {
    if (item->type == ITEM::TYPE::PISTOL) ammo += 20;
    if (item->type == ITEM::TYPE::POTION) potions += 1;
    for (int i = 0; i < items_length; i++) {
        if (items[i] == item) {
            if (level != NULL) level->showLootScreen(item);
            return;
        }
    }

    for (int i = 0; i < items_length; i++) {
        if (items[i]->type == ITEM::TYPE::NONE) {
            items[i] = item;
            selectedSlot = i;
            itemUseTime = 0;
            if (level != NULL) level->showLootScreen(item);
            return;
        }
    }
}

void Player::hurt(Entity* enemy, int dmg) {
    if (hurtTime > 0 || dead) return;
    // trace("PLAYER::HURT", enemy->getName(enemy->type()) + ": " + tstr(dmg));

    hurtTime = 40;
    health -= dmg;

    if (health <= 0) {
        health = 0;
        sound.death->play();
        dead = true;
    }

    sound.hurt->play();

    double xd = enemy->x - x;
    double zd = enemy->z - z;
    double dd = math.sqrt(xd * xd + zd * zd);
    xa -= xd / dd * 0.1;
    za -= zd / dd * 0.1;
    Random rnd;
    rota += (rnd.nextDouble() - 0.5) * 0.2;
}

void Player::collide(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::BULLET) {
        Bullet* bullet = (Bullet*)entity;
        if (bullet->owner == this) {
            return;
        }
        if (hurtTime > 0) return;
        entity->remove();
        hurt(entity, 1);
    }
}

void Player::win() {
    level->win();
}