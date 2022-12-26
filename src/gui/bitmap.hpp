#ifndef POTC_BITMAP_H
#define POTC_BITMAP_H

#include <string>

#include "../utils/trace.hpp"

class Bitmap {
    public:
        int width, height;
        int* pixels;
        int length;
        std::string chars;
        // constexpr static char chars[] = {
        //     '\0',
        //     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
        //     '.', ',', '!', '?', '\"', '\'', '/', '\\', '<', '>', '(', ')', '[', ']', '{', '}',
        //     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
        //     '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        //     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '=', '*', ':', ';', ' ', ' ', ' ', ' ',
        //     ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        //     '\0',
        // };

        Bitmap(int width, int height) : width(width), height(height) {
            pixels = new int[width * height];
            length = width * height;
            
            chars = std::string("") +
            std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?\"'/\\<>()[]{}") + // + 42
			std::string("abcdefghijklmnopqrstuvwxyz_               "  ) + // + 42
			std::string("0123456789+-=*:;#$%^                      "  ) + //   42 = 126
            std::string("");
        }

        ~Bitmap() {
            delete pixels;
        }

        void draw(Bitmap* bitmap, int xOffs, int yOffs);
        void draw(Bitmap* bitmap, int xOffs, int yOffs, int xo, int yo, int w, int h, int col);
        void draw(std::string string, int x, int y, int col);
        void flipDraw(Bitmap* bitmap, int xOffs, int yOffs);
        void scaleDraw(Bitmap* bitmap, int scale, int xOffs, int yOffs, int xo, int yo, int w, int h, int col);
        void fill(int x0, int y0, int x1, int y1, int color);

    protected:
        Bitmap() = default;
};

#endif // POTC_BITMAP_H