#ifndef POTC_SCREEN_H
#define POTC_SCREEN_H

#include "../game.hpp"

#include "bitmap.hpp"
#include "bitmap3d.hpp"

#include "../utils/random.hpp"
#include "../utils/trace.hpp"

class Screen : public Bitmap {
    private:
        int PANEL_HEIGHT;
        Bitmap3D* viewport;
    public:
        Screen(int width, int height) : Bitmap(width, height) {
            PANEL_HEIGHT = 29;
            Random random;
            // trace("WIDTH", width);
            viewport = new Bitmap3D(width, height - PANEL_HEIGHT);

            // for (int i = 0; i < width * height; i++) {
            //     pixels[i] = random.nextInt() * (random.nextInt(5) / 4);
            // }
        }

        ~Screen() {
            delete viewport;
        }

        void render(Game* game, bool hasFocus);
};

#endif // POTC_SCREEN_H