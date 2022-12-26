#ifndef POTC_SPRITE_RUBBLE_H
#define POTC_SPRITE_RUBBLE_H

#include "sprite.hpp"

#include "../utils/math.hpp"

static Math math;

class RubbleSprite : public Sprite {
private:
    double xa, ya, za;
public:
    RubbleSprite() :
    Sprite(math.random() - 0.5, math.random() * 0.8, math.random() - 0.5,
        2, 0x555555) {
        xa = math.random() - 0.5;
		ya = math.random();
		za = math.random() - 0.5;
    }
    void tick() override {
        x += xa * 0.03;
        y += ya * 0.03;
        z += za * 0.03;
        ya -= 0.1;
        if (y < 0) {
            y = 0;
            xa *= 0.8;
            za *= 0.8;
            if (math.random() < 0.04) removed = true;
        }
    }
};

#endif // POTC_SPRITE_RUBBLE_H