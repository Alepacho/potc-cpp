#ifndef POTC_ITEM_H
#define POTC_ITEM_H

#include <string>

namespace ITEM {
    enum TYPE {
        NONE,
        POWER_GLOVE,
        PISTOL,
        FLIPPERS,
        CUTTERS,
        SKATES,
        KEY,
        POTION,
    };
}

class Item {
public:
    int icon, color;
    ITEM::TYPE type = ITEM::TYPE::NONE;
    std::string name, description;
    Item(int icon, int color, ITEM::TYPE type, std::string name, std::string description) :
        icon(icon), color(color), type(type), name(name), description(description) {};
};

namespace ITEM {
    static Item none         (-1, 0xFFC363, ITEM::TYPE::NONE,        "",              "");
    static Item powerGlove   ( 0, 0xFFC363, ITEM::TYPE::POWER_GLOVE, "Power Glove",   "Smaaaash!!");
    static Item pistol       ( 1, 0xEAEAEA, ITEM::TYPE::PISTOL,      "Pistol",        "Pew, pew, pew!");
    static Item flippers     ( 2, 0x7CBBFF, ITEM::TYPE::FLIPPERS,    "Flippers",      "Splish splash!");
    static Item cutters      ( 3, 0xCCCCCC, ITEM::TYPE::CUTTERS,     "Cutters",       "Snip, snip!");
    static Item skates       ( 4, 0xAE70FF, ITEM::TYPE::SKATES,      "Skates", 	      "Sharp!");
    static Item key          ( 5, 0xFF4040, ITEM::TYPE::KEY,         "Key",           "How did you get this?");
    static Item potion       ( 6, 0x4AFF47, ITEM::TYPE::POTION,      "Potion", 	      "Healthy!"); 
};

#endif // POTC_ITEM_H