#ifndef POTC_SOUND_H
#define POTC_SOUND_H

#include <string>
#include "utils/trace.hpp"

#include <SDL.h>
#include <SDL_mixer.h>

// static SDL_AudioDeviceID device;

// void SoundInit() {

// }

// void SoundTerm() {
//     SDL_CloseAudioDevice(device);
// }

class SFX {
public:    
    Mix_Chunk* chunk;

    SFX() {
        chunk = NULL;
    }
    ~SFX() {
        if (chunk) Mix_FreeChunk(chunk);
    }
    
    void play();
};

class Sound {
public:
    int volume_sfx, volume_music;

    SFX* altar;
    SFX* bosskill;
    SFX* click1;
    SFX* click2;
    SFX* hit;
    SFX* hurt;
    SFX* hurt2;
    SFX* kill;
    SFX* death;
    SFX* splash;
    SFX* key;
    SFX* pickup;
    SFX* roll;
    SFX* shoot;
    SFX* treasure;
    SFX* crumble;
    SFX* slide;
    SFX* cut;
    SFX* thud;
    SFX* ladder;
    SFX* potion;

    Sound() {
        volume_sfx   = 10;
        volume_music = 10;
    }

    void init() {
        trace("init");
        altar     = loadSound("res/snd/altar.wav");
        bosskill  = loadSound("res/snd/bosskill.wav");
        click1    = loadSound("res/snd/click.wav");
        click2    = loadSound("res/snd/click2.wav");
        hit       = loadSound("res/snd/hit.wav");
        hurt      = loadSound("res/snd/hurt.wav");
        hurt2     = loadSound("res/snd/hurt2.wav");
        kill      = loadSound("res/snd/kill.wav");
        death     = loadSound("res/snd/death.wav");
        splash    = loadSound("res/snd/splash.wav");
        key       = loadSound("res/snd/key.wav");
        pickup    = loadSound("res/snd/pickup.wav");
        roll      = loadSound("res/snd/roll.wav");
        shoot     = loadSound("res/snd/shoot.wav");
        treasure  = loadSound("res/snd/treasure.wav");
        crumble   = loadSound("res/snd/crumble.wav");
        slide     = loadSound("res/snd/slide.wav");
        cut       = loadSound("res/snd/cut.wav");
        thud      = loadSound("res/snd/thud.wav");
        ladder    = loadSound("res/snd/ladder.wav");
        potion    = loadSound("res/snd/potion.wav");
    }

    SFX* loadSound(std::string fileName);
};

// namespace SFX {
//     static Sound* altar;
//     static Sound* bosskill;
//     static Sound* click1;
//     static Sound* click2;
//     static Sound* hit;
//     static Sound* hurt;
//     static Sound* hurt2;
//     static Sound* kill;
//     static Sound* death;
//     static Sound* splash;
//     static Sound* key;
//     static Sound* pickup;
//     static Sound* roll;
//     static Sound* shoot;
//     static Sound* treasure;
//     static Sound* crumble;
//     static Sound* slide;
//     static Sound* cut;
//     static Sound* thud;
//     static Sound* ladder;
//     static Sound* potion;

//     inline void init() {
//         altar     = new Sound("res/snd/altar.wav");
//         bosskill  = new Sound("res/snd/bosskill.wav");
//         click1    = new Sound("res/snd/click.wav");
//         click2    = new Sound("res/snd/click2.wav");
//         hit       = new Sound("res/snd/hit.wav");
//         hurt      = new Sound("res/snd/hurt.wav");
//         hurt2     = new Sound("res/snd/hurt2.wav");
//         kill      = new Sound("res/snd/kill.wav");
//         death     = new Sound("res/snd/death.wav");
//         splash    = new Sound("res/snd/splash.wav");
//         key       = new Sound("res/snd/key.wav");
//         pickup    = new Sound("res/snd/pickup.wav");
//         roll      = new Sound("res/snd/roll.wav");
//         shoot     = new Sound("res/snd/shoot.wav");
//         treasure  = new Sound("res/snd/treasure.wav");
//         crumble   = new Sound("res/snd/crumble.wav");
//         slide     = new Sound("res/snd/slide.wav");
//         cut       = new Sound("res/snd/cut.wav");
//         thud      = new Sound("res/snd/thud.wav");
//         ladder    = new Sound("res/snd/ladder.wav");
//         potion    = new Sound("res/snd/potion.wav");
//     }
// };

#endif // POTC_SOUND_H