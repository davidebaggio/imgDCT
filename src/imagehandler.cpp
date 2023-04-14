#include "imagehandler.hpp"

void convertRGBtoYCbCr(SDL_Surface *src, SDL_Surface *dest)
{

	// locking surfaces to easily access the pixels
	SDL_LockSurface(src);
	SDL_LockSurface(dest);

	int w = src->w;
	int h = src->h;
	Uint32 *srcPixels = (Uint32 *)src->pixels;
	Uint32 *destPixels = (Uint32 *)dest->pixels;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			Uint32 pixel = srcPixels[y * w + x];
			Uint8 R = (pixel >> 16) & 0xFF;
			Uint8 G = (pixel >> 8) & 0xFF;
			Uint8 B = pixel & 0xFF;

			Uint8 Y = 0.299 * R + 0.587 * G + 0.114 * B;
			Uint8 Cb = 128 - 0.168736 * R - 0.331264 * G + 0.5 * B;
			Uint8 Cr = 128 + 0.5 * R - 0.418688 * G - 0.081312 * B;

			destPixels[y * w + x] = SDL_MapRGB(dest->format, Cr, Cb, Y);
		}
	}

	SDL_UnlockSurface(src);
	SDL_UnlockSurface(dest);
}

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