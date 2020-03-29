#include "gfx/gfx.h"
#include "gfx_linux/globals.h"
#include "cdefs.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

static SDL_Surface* g_font;

/**
 * Loads text texture.
 */
void gfx_init_text(void)
{
	SDL_Surface* font_surface = SDL_LoadBMP("res/mda_tiles.bmp");
	if (font_surface == NULL)
	{
		SDL_Log("Unable to load image: %s", SDL_GetError());
		abort();
	}

	g_font = SDL_ConvertSurface(font_surface, g_surface->format, 0);
	if (g_font == NULL)
	{
		SDL_Log("Unable to convert image: %s", SDL_GetError());
		abort();
	}
}

/**
 * Sets the character at a location on screen.
 */
void gfx_set_char(unsigned int x, unsigned int y, unsigned char c)
{
	if (x >= gfx_width() || y >= gfx_height())
		return;

	SDL_Rect source =
	{
		.x = 9 * (c % 32),
		.y = 14 * (c / 32),
		.w = 9,
		.h = 14
	};

	SDL_Rect destination =
	{
		.x = 9 * x,
		.y = 14 * y,
		.w = 9,
		.h = 14
	};

	SDL_BlitSurface(g_font, &source, g_surface, &destination);
}

/**
 * Clear the screen.
 */
void gfx_clear(void)
{
	SDL_FillRect(g_surface, NULL, SDL_MapRGB(g_surface->format, 0, 0, 0));
}
