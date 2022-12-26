# C++ port of 'Prelude of the Chambered'

[](./screenshots/title.png)

### _Made by me, only for study purpose_.
Based on original source code which I got [here](https://github.com/skeeto/Prelude-of-the-Chambered). And I used to watch some old Notch streams to understand some stuff. You can watch streams [here](https://www.youtube.com/@hikearchive/videos) (thanks to Hike's Archive).

# Screenshots

[](./screenshots/game.png)
[](./screenshots/win.png)

# Disclaimer
Game is fully completable, but...

Due the differences of both Java and C++, this port may be not 100% equal to original, but I've tried to save all possible mechanics as far as possible.

Port is hard-locked to 60 FPS, doesn't use Threads and, instead of Java's AWT, uses SDL2. Also, I've put some Java related stuff (math, random) into `utils` folder.

# How to run
First of all, install `SDL2`, `SDL2_Image` and `SDL2_mixer` on your PC:

## For macOS (using brew):
```
brew install sdl2 sdl2_image sdl2_mixer
```

## For Windows:
I didn't test it on Windows, but you can use MinGW to compile it.

## Compilation:
You can use my own [build tool](https://github.com/Alepacho/build) or just compile by using `make`:
```
./build main
```
or
```
make
```
respectively.

# Known bugs
* Torch can be placed on a wrong position;
* Player timer doesn't work correctly;
# License
See [LICENSE](./LICENSE)

TL;DR It's MIT 