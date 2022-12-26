#include "sound.hpp"

#include "utils/trace.hpp"

SFX* Sound::loadSound(std::string fileName) {
    trace("SOUND::LOAD", fileName);
    SFX* sfx = NULL;

    try {
        sfx = new SFX();
        sfx->chunk = Mix_LoadWAV(fileName.c_str());
        if (sfx->chunk == NULL) {
            trace("SOUND::LOAD", fileName + " " + SDL_GetError());
            return NULL;
        }
    } catch(std::exception e) {
        trace("SOUND::LOAD", e.what());
    }

    return sfx;
}

void SFX::play() {
    try {
        if (chunk == NULL) return;
        if (Mix_PlayChannel(-1, chunk, 0) == -1) {
            trace("SOUND::PLAY", "Unable to play sound!");
        }
    } catch(std::exception e) {
        trace("SOUND::PLAY", e.what());
    }
}


