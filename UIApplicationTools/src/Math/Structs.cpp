#include "Structs.h"

#include <SDL.h>

ColorRGB::operator SDL_Color()
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;

	return color;
}

ColorRGBA::operator SDL_Color()
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	return color;
}
