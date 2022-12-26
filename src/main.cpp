#include "game.hpp"
#include "engine.hpp"
#include "gui/screen.hpp"

int main(int argc, char* argv[]) {
    Game* game = new Game();
    Engine engine(game);
    
    engine.start();

    while (engine.isRunning()) {
        engine.tick();
        engine.render();
    }

    engine.stop();

    delete game;
    return 0;
}