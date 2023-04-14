#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void convertRGBtoYCbCr(SDL_Surface *, SDL_Surface *);
Uint32 getpixel(SDL_Surface *, int, int);

#endif