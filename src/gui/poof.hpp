#ifndef POTC_SPRITE_POOF_H
#define POTC_SPRITE_POOF_H

#include "sprite.hpp"

class PoofSprite : public Sprite {
private:
    int life;
public:
    PoofSprite() {
        life = 20;
    }

    PoofSprite(double x, double y, double z)
        : Sprite(x, y, z, 5, 0x222222) {}

    void tick() override {
        if (life-- <= 0) removed = true;
    }
};

#endif // POTC_SPRITE_POOF_H