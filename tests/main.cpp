#include <iostream>
#include "imagehandler.hpp"

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

	/* SDL_Color rgb;
	for (size_t i = 0; i < 400; i++)
	{
		for (size_t j = 0; j < 400; j++)
		{
			Uint32 data = getpixel(image, i, j);
			SDL_GetRGB(data, image->format, &rgb.r, &rgb.g, &rgb.b);
			std::cout << std::hex << "0x " << data << " ";
		}
		std::cout << "\n";
	} */

	/* Uint32 data = getpixel(image, i, j);
	SDL_GetRGB(data, image->format, &rgb.r, &rgb.g, &rgb.b); */

	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_Surface *out = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	convertRGBtoYCbCr(image, out);
	IMG_SavePNG(out, "out.png");

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(image);
	SDL_FreeSurface(out);
	IMG_Quit();

	SDL_Quit();
	return 0;
}
