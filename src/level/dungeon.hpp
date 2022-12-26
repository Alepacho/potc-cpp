#ifndef POTC_LEVEL_DUNGEON_H
#define POTC_LEVEL_DUNGEON_H

#include "level.hpp"

class DungeonLevel : public Level {
public:
    DungeonLevel() {
        trace("LEVEL::INIT", "DUNGEON");
        wallCol  = 0xC64954;
		floorCol = 0x8E4A51;
		ceilCol  = 0x8E4A51;
        name = "The Dungeons";
    }

	void init(Game* game, std::string name, Bitmap* bitmap) override;
    void switchLevel(int id) override;
    void getLoot(int id) override;
    void trigger(int id, bool pressed) override;
};

#endif // POTC_LEVEL_DUNGEON_H