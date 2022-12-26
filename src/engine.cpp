#include "engine.hpp"
#include "sound.hpp"

#include "utils/trace.hpp"
#include "utils/input.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Uint64 interval, end, now, ms_interval;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* img;
int WW;
int HH;
int RATIO;
bool keys[KEY_EVENT::COUNT];
Sound sound;


void handle_keyboard(int key, bool pressed) {
    switch (key) {
        case SDLK_ESCAPE : keys[KEY_EVENT::ESCAPE]    = pressed; break;
        case SDLK_LCTRL  : keys[KEY_EVENT::CONTROL]   = pressed; break;
        case SDLK_LALT   : keys[KEY_EVENT::ALT]       = pressed; break;
        case SDLK_MODE   : keys[KEY_EVENT::ALT_GRAPH] = pressed; break;
        case SDLK_SPACE  : keys[KEY_EVENT::SPACE]     = pressed; break;
        case SDLK_RETURN : keys[KEY_EVENT::ENTER]     = pressed; break;
        case SDLK_LEFT   : keys[KEY_EVENT::LEFT]      = pressed; break;
        case SDLK_RIGHT  : keys[KEY_EVENT::RIGHT]     = pressed; break;
        case SDLK_UP     : keys[KEY_EVENT::UP]        = pressed; break;
        case SDLK_DOWN   : keys[KEY_EVENT::DOWN]      = pressed; break;
        case SDLK_w      : keys[KEY_EVENT::W]         = pressed; break;
        case SDLK_a      : keys[KEY_EVENT::A]         = pressed; break;
        case SDLK_s      : keys[KEY_EVENT::S]         = pressed; break;
        case SDLK_d      : keys[KEY_EVENT::D]         = pressed; break;
        case SDLK_q      : keys[KEY_EVENT::Q]         = pressed; break;
        case SDLK_e      : keys[KEY_EVENT::E]         = pressed; break;
        case SDLK_KP_2   : keys[KEY_EVENT::NUMPAD2]   = pressed; break;
        case SDLK_KP_4   : keys[KEY_EVENT::NUMPAD4]   = pressed; break;
        case SDLK_KP_6   : keys[KEY_EVENT::NUMPAD6]   = pressed; break;
        case SDLK_KP_8   : keys[KEY_EVENT::NUMPAD8]   = pressed; break;
        case SDLK_0      : keys[KEY_EVENT::K0]        = pressed; break;
        case SDLK_1      : keys[KEY_EVENT::K1]        = pressed; break;
        case SDLK_2      : keys[KEY_EVENT::K2]        = pressed; break;
        case SDLK_3      : keys[KEY_EVENT::K3]        = pressed; break;
        case SDLK_4      : keys[KEY_EVENT::K4]        = pressed; break;
        case SDLK_5      : keys[KEY_EVENT::K5]        = pressed; break;
        case SDLK_6      : keys[KEY_EVENT::K6]        = pressed; break;
        case SDLK_7      : keys[KEY_EVENT::K7]        = pressed; break;
        case SDLK_8      : keys[KEY_EVENT::K8]        = pressed; break;
        case SDLK_9      : keys[KEY_EVENT::K9]        = pressed; break;
    }
}

void resize(int width, int height) {
    SDL_GetWindowSize(window, &WW, &HH);
    RATIO = fmin(
        (float)WW / (float)width, 
        (float)HH / (float)height
    );

}

void Engine::start() {
    if (running) return;
    running = true;
    hadFocus = true;

    WW = WIDTH  * SCALE;
    HH = HEIGHT * SCALE;

    // SDL2 init
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        trace(SDL_GetError());
        running = false; return;
    }

    Uint32 window_flags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("Prelude of the Chambered!", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WW, HH, window_flags);
    if (window == NULL) {
        trace(SDL_GetError());
        running = false; return;
    }

    renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        trace(SDL_GetError());
        running = false; return;
    }

    img = SDL_CreateTexture(renderer,  // SDL_PIXELFORMAT_RGBA32
        SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, // SDL_TEXTUREACCESS_STREAMING
        WIDTH, HEIGHT);
    if (screen == NULL) {
        trace(SDL_GetError());
        running = false; return;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        trace(SDL_GetError());
        running = false; return;
    }

    const int mix_flags = MIX_INIT_OGG;
    int result = Mix_Init(mix_flags);

    if ((result & mix_flags) == mix_flags) {
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) {
            Mix_Volume(-1,  MIX_MAX_VOLUME * sound.volume_sfx   / 100);
            Mix_VolumeMusic(MIX_MAX_VOLUME * sound.volume_music / 100);
        } else {
            trace("SOUND::INIT", Mix_GetError());
            running = false; return;
        }
    } else {
        trace("SOUND::INIT", SDL_GetError());
        running = false; return;
    }

    now         = SDL_GetPerformanceCounter();
    interval    = SDL_GetPerformanceFrequency() / 60;
    ms_interval = SDL_GetPerformanceFrequency() / 1000;
    SDL_RenderSetVSync(renderer, true);

    resize(WIDTH, HEIGHT);

    sound.init();
}

void Engine::stop() {
    if (!running) return;
    running = false;

    Mix_CloseAudio();
    IMG_Quit();
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::tick() {
    end = now + interval;
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: running = false; break;
            case SDL_WINDOWEVENT: {
                switch(e.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        resize(WIDTH, HEIGHT);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        hasFocus = false;
                        for (int i = 0; i < KEY_EVENT::COUNT; i++) {
                            keys[i] = false;
                        }
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        hasFocus = true;
                        break;
                }
            } break;
            case SDL_KEYDOWN: {
                SDL_Keycode k = e.key.keysym.sym;
                handle_keyboard(k, true);
            } break;
            case SDL_KEYUP: {
                SDL_Keycode k = e.key.keysym.sym;
                handle_keyboard(k, false);
            } break;
            default:
                break;
        }
    }


    if (hasFocus) {
        game->tick(keys);
    }

    if (game->exit) running = false;

    now = SDL_GetPerformanceCounter();
    Sint64 delay = end - now;
    if (delay > 0) {
        SDL_Delay((Uint64)delay / ms_interval);
        now = end;
    }
}

void Engine::render() {
    screen->render(game, hasFocus); 

    int *pixels = NULL;
    int pitch;
    if (SDL_LockTexture(img, NULL, (void **)&pixels, &pitch)) {
        trace("RENDER::ERROR", "Cannot lock screen texture!");
        running = false;
        return;
    }
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        pixels[i] = screen->pixels[i];
    }
    // memcpy(pixels, screen->pixels, (WIDTH * HEIGHT) * sizeof(int));
    SDL_UnlockTexture(img);

    SDL_Rect spos;
    spos.x = (int)(WW - WIDTH  * RATIO) / 2;
    spos.y = (int)(HH - HEIGHT * RATIO) / 2;
    spos.w = (int)(WIDTH  * RATIO);
    spos.h = (int)(HEIGHT * RATIO);

    SDL_RenderCopy(renderer, img, NULL, &spos);
    SDL_Rect viewport = { 0, 0, WW, HH };
    SDL_RenderSetViewport(renderer, &viewport);

    SDL_RenderPresent(renderer);
}