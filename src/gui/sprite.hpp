#ifndef POTC_SPRITE_H
#define POTC_SPRITE_H

class Sprite {
    public:
    double x, y, z;
    int tex;
    int color = 0x202020;
    bool removed = false;

    Sprite() {};

    Sprite(double x, double y, double z, int tex, int color) :
        x(x), y(y), z(z), tex(tex), color(color) {}

    virtual void tick() {};
};

#endif // POTC_SPRITE_H