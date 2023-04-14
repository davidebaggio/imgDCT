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
	SDL_Window *window = SDL_CreateWindow("image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface *image = IMG_Load("./img/lettuce.png");
	if (image == NULL)
	{
		std::cout << "image not opened\n"
				  << IMG_GetError();
		exit(1);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Color rgb;
	Uint32 data = getpixel(image, 200, 200);
	SDL_GetRGB(data, image->format, &rgb.r, &rgb.g, &rgb.b);

	while (1)
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(image);
	IMG_Quit();
	std::cout << data << "\n";

	SDL_Quit();
	return 0;
}
