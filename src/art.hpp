#ifndef POTC_ART_H
#define POTC_ART_H

#include "gui/bitmap.hpp"

class Art {
public:
    Bitmap* walls;
    Bitmap* floors;
    Bitmap* sprites;
    Bitmap* font;
    Bitmap* panel;
    Bitmap* items;
    Bitmap* sky;
    Bitmap* logo;

    Art() {
        walls    = loadBitmap("res/tex/walls.png");
        floors   = loadBitmap("res/tex/floors.png");
        sprites  = loadBitmap("res/tex/sprites.png");
        font     = loadBitmap("res/tex/font.png");
        panel    = loadBitmap("res/tex/gamepanel.png");
        items    = loadBitmap("res/tex/items.png");
        sky      = loadBitmap("res/tex/sky.png");
        logo     = loadBitmap("res/gui/logo.png");
    }

    ~Art() {
        delete walls  ;
        delete floors ;
        delete sprites;
        delete font   ;
        delete panel  ;
        delete items  ;
        delete sky    ;
        delete logo   ;
    }

    Bitmap* loadBitmap(std::string fileName);
    Bitmap* loadLevel(std::string fileName);
    int getCol(int c) {
        int r = (c >> 16) & 0xff;
		int g = (c >> 8)  & 0xff;
		int b = (c)       & 0xff;

		r = r * 0x55 / 0xff;
		g = g * 0x55 / 0xff;
		b = b * 0x55 / 0xff;

		return r << 16 | g << 8 | b;
    }
};

static Art art;

#endif // POTC_ART_H