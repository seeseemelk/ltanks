#include <gfx_linux/globals.h>

/// The game window
SDL_Window* g_window;

/// The game surface
SDL_Surface* g_surface;

/**
 * Gets the number of characters that can be shown
 * in one horizontal row.
 */
unsigned int gfx_width(void)
{
	return GFX_CHAR_WIDTH;
}

/**
 * Gets the number of characters that can be shown
 * in one vertical column.
 */
unsigned int gfx_height(void)
{
	return GFX_CHAR_HEIGHT;
}
