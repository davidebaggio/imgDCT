#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	// std::cout << bpp << "\n";
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL error\n";
	}
	else
	{
		std::cout << "SDL Init\n";
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Error SDL2_image Initialization";
		return 2;
	}

	SDL_Surface *image = IMG_Load("lettuce.png");
	if (!image)
	{
		std::cout << "image not opened\n";
		exit(1);
	}
	SDL_Color rgb;
	Uint32 data = getpixel(image, 200, 200);
	SDL_GetRGB(data, image->format, &rgb.r, &rgb.g, &rgb.b);

	SDL_FreeSurface(image);

	std::cout << data << "\n";

	SDL_Quit();
	return 0;
}
