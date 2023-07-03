#include "art.hpp"

#include "utils/trace.hpp"

#include <SDL.h>
#include <SDL_image.h>

Bitmap* Art::loadBitmap(std::string fileName) {
    trace("ART::BITMAP::LOAD", fileName);
    try {
        SDL_Surface* img = IMG_Load(fileName.c_str());
        if (img == NULL) {
            trace("ART::BITMAP::ERROR", SDL_GetError());
            return NULL;
        }
        // trace("format", fileName + " " + SDL_GetPixelFormatName(img->format->format));

        int w = img->w;
        int h = img->h;
        Bitmap* result = new Bitmap(w, h);

        if (SDL_LockSurface(img)) {
            trace("ART::BITMAP::ERROR", SDL_GetError());
            return NULL;
        }
        
        int* p = (int*)img->pixels;
        for (int i = 0; i < w * h; i++) {
            int in = *(p + i);
            int col = (in & 0xf) >> 2;
            if (in == 0xffff00ff) col = -1;
            result->pixels[i] = col;
        }
        SDL_UnlockSurface(img);
        SDL_FreeSurface(img);
        return result;
    } catch(std::exception e) {
        trace("ART::BITMAP::ERROR", e.what());
        return NULL;
    }
}

Bitmap* Art::loadLevel(std::string fileName) {
    trace("ART::LEVEL::LOAD", fileName);
    try {
        SDL_Surface* img = IMG_Load(fileName.c_str());
        if (img == NULL) {
            trace("ART::LEVEL::ERROR", SDL_GetError());
            return NULL;
        }
        // trace("format", fileName + " " + SDL_GetPixelFormatName(img->format->format));

        int w = img->w;
        int h = img->h;
        Bitmap* result = new Bitmap(w, h);

        if (SDL_LockSurface(img)) {
            trace("ART::LEVEL::ERROR", SDL_GetError());
            return NULL;
        }
        
        int* p = (int*)img->pixels;
        Uint8 r, g, b, a;
        for (int i = 0; i < w * h; i++) {
            Uint32 in = *(p + i);
            SDL_GetRGBA(in, img->format, &r, &g, &b, &a);
            // trace("COLOR", hex((int)r) + ", " + hex((int)g) + ", " + hex((int)b));
            int col = Uint32((Uint8)(a) << 24 | (Uint8)(r) << 16 | (Uint8)(g) << 8 | (Uint8)(b));
            // if (col > 0) trace("COLOR", hex(col));
            // int col = (in & 0xf) >> 2;
            // if (in == 0xffff00ff) col = -1;
            result->pixels[i] = col;
        }
        SDL_UnlockSurface(img);
        SDL_FreeSurface(img);
        return result;
    } catch(std::exception e) {
        trace("ART::LEVEL::ERROR", e.what());
        return NULL;
    }
}