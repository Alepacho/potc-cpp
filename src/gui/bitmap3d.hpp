#ifndef POTC_BITMAP3D_H
#define POTC_BITMAP3D_H

#include <string>

#include "bitmap.hpp"
#include "../game.hpp"
#include "../level/level.hpp"

class Bitmap3D : public Bitmap {
    private:
        double* zBuffer;
        double* zBufferWall;
        double xCam, yCam, zCam, rCos, rSin, fov, xCenter, yCenter, rot;
        
        void renderFloor(Level* level);
        void renderSprite(double x, double y, double z, int tex, int color);
        void renderWall(double x0, double y0, double x1, double y1, int tex, int color);
        void renderWall(double x0, double y0, double x1, double y1, int tex, int color, double xt0, double xt1);
    public:
        Bitmap3D(int width, int height) : Bitmap(width, height) {
            this->width = width;
            this->height = height;

            zBuffer = new double[width * height];
            zBufferWall = new double[width];
        }

        ~Bitmap3D() {
            delete zBuffer;
            delete zBufferWall;
        }

        void render(Game* game);
        void postProcess(Level* level);
};

#endif // POTC_BITMAP3D_H