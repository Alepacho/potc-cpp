#include "enemy.hpp"

#include "player.hpp"
#include "bullet.hpp"
#include "key.hpp"

#include "bat.hpp"
#include "bat_boss.hpp"
#include "ogre.hpp"
#include "ogre_boss.hpp"
#include "ghost.hpp"
#include "ghost_boss.hpp"
// #include "eye.hpp"
#include "eye_boss.hpp"

#include "../gui/poof.hpp"

#include "../art.hpp"
#include "../sound.hpp"
#include "../utils/math.hpp"
#include "../utils/random.hpp"

extern Sound sound;
static Math math;
Random rnd;

void EnemyEntity::tick() {
    if (hurtTime > 0) {
        hurtTime--;
        if (hurtTime == 0) {
            sprite->color = defaultColor;
        }
    }
    animTime++;
    sprite->tex = defaultTex + animTime / 10 % 2;
    move();
    if (xa == 0 || za == 0) {
        rota += (rnd.nextGaussian() * rnd.nextDouble()) * 0.3;
    }

    rota += (rnd.nextGaussian() * rnd.nextDouble()) * spinSpeed;
    rot += rota;
    rota *= 0.8;
    xa *= 0.8;
    za *= 0.8;
    xa += math.sin(rot) * 0.004 * runSpeed;
    za += math.cos(rot) * 0.004 * runSpeed;
}

bool EnemyEntity::use(Entity* source, Item* item) {
    if (hurtTime > 0) return false;
    if (item->type != ITEM::TYPE::POWER_GLOVE) return false;

    hurt(math.sin(source->rot), math.cos(source->rot));

    return true;
}

void EnemyEntity::hurt(double xd, double zd) {
    sprite->color = art.getCol(0xff0000);
    hurtTime = 15;

    double dd = math.sqrt(xd * xd + zd * zd);
    xa += xd / dd * 0.2;
    za += zd / dd * 0.2;
    sound.hurt2->play();
    health--;
    if (health <= 0) {
        int xt = (int) (x + 0.5);
        int zt = (int) (z + 0.5);
        level->getBlock(xt, zt)->addSprite(new PoofSprite(x - xt, 0, z - zt));
        die(); remove();
        sound.kill->play();
    }
}

void EnemyEntity::collide(Entity* entity) {
    if (entity->type() == ENTITY::TYPE::BULLET) {
        Bullet* bullet = (Bullet*) entity;
        if (bullet->owner == this) {
            return;
        }
        if (hurtTime > 0) return;
        entity->remove();
        hurt(entity->xa, entity->za);
    }
    if (entity->type() == ENTITY::TYPE::PLAYER) {
        ((Player*)entity)->hurt(this, 1);
    }
}

void BatBossEntity::die() {
    sound.bosskill->play();
	level->addEntity(new KeyEntity(x, z));
}

void BatBossEntity::tick() {
    EnemyEntity::tick();
    if (rnd.nextInt(20) == 0) {
        double xx = x + (rnd.nextDouble() - 0.5) * 2;
        double zz = z + (rnd.nextDouble() - 0.5) * 2;
        BatEntity* batEntity = new BatEntity(xx, zz);
        batEntity->level = level;

        batEntity->x = -999;
        batEntity->z = -999;
        
        if (batEntity->isFree(xx, zz)) {
            level->addEntity(batEntity);
        }
    }
}

void OgreEntity::hurt(double xd, double zd) {
    EnemyEntity::hurt(xd, zd);
    shootDelay = 50;
}

void OgreEntity::tick() {
    EnemyEntity::tick();
    if (shootDelay > 0) shootDelay--; else if (rnd.nextInt(40) == 0) {
        shootDelay = 40;
        level->addEntity(new Bullet(this, x, z,
            math.atan2(level->player->x - x, level->player->z - z),
            0.3, 1, defaultColor
        ));
    }
}


void OgreBossEntity::die() {
    sound.bosskill->play();
	level->addEntity(new KeyEntity(x, z));
}

void OgreBossEntity::tick() {
    EnemyEntity::tick();
    if (shootDelay > 0) shootDelay--;
    else {
        shootDelay = 5;
        int salva = 10;

        for (int i = 0; i < 4; i++) {
            double rot = math.PI / 2 * (i + shootPhase / salva % 2 * 0.5);
            level->addEntity(new Bullet(this, x, z, rot, 0.4, 1, defaultColor));
        }

        shootPhase++;
        if (shootPhase % salva == 0) shootDelay = 40;
    }
}

void GhostEntity::tick() {
    animTime++;
    sprite->tex = defaultTex + animTime / 10 % 2;

    double xd = (level->player->x + math.sin(rotatePos)) - x;
    double zd = (level->player->z + math.cos(rotatePos)) - z;
    double dd = xd * xd + zd * zd;

    if (dd < 4 * 4) {
        if (dd < 1) {
            rotatePos += 0.04;
        } else {
            rotatePos = level->player->rot;
            xa += (rnd.nextDouble() - 0.5) * 0.02;
            za += (rnd.nextDouble() - 0.5) * 0.02;
        }
        
        dd = math.sqrt(dd);

        xd /= dd;
        zd /= dd;

        xa += xd * 0.004;
        za += zd * 0.004;
    }

    move();

    xa *= 0.9;
    za *= 0.9;
}

void GhostBossEntity::tick() {
    animTime++;
    sprite->tex = defaultTex + animTime / 10 % 2;

    double xd = (level->player->x + math.sin(rotatePos) * 2) - x;
    double zd = (level->player->z + math.cos(rotatePos) * 2) - z;
    double dd = xd * xd + zd * zd;

    if (dd < 1) {
        rotatePos += 0.04;
    } else {
        rotatePos = level->player->rot;
    }
    if (dd < 4 * 4) {
        dd = math.sqrt(dd);

        xd /= dd;
        zd /= dd;

        xa += xd * 0.006;
        za += zd * 0.006;
        
        if (shootDelay > 0) shootDelay--;
        else if (rnd.nextInt(10) == 0) {
            shootDelay = 10;
            level->addEntity(new Bullet(this, x, z, 
                math.atan2(level->player->x - x, level->player->z - z), 
                0.20, 1, defaultColor
            ));
        }

    }

    move();

    xa *= 0.9;
    za *= 0.9;
}

void EyeBossEntity::die() {
    sound.bosskill->play();
	level->addEntity(new KeyEntity(x, z));
}