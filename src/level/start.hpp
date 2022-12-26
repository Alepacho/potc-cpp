#ifndef POTC_LEVEL_START_H
#define POTC_LEVEL_START_H

#include "level.hpp"

class StartLevel : public Level {
public:
    StartLevel() { //  : Level() 
        name = "The Prison";
        trace("LEVEL::INIT", "START");
    }

    // protected
    void decorateBlock(int x, int y, Block* block, int col) override {
        Level::decorateBlock(x, y, block, col);
    }

    // protected
    Block* getBlock(int x, int y, int col) override {
        return Level::getBlock(x, y, col);
    }

    void switchLevel(int id) override; // ! see level.cpp

    void getLoot(int id) override {
        Level::getLoot(id);
    }
};

#endif // POTC_LEVEL_START_H