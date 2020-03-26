#include "gfx/gfx.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * Setup and run graphics.
 *
 * @return `true` normally
 * @return `false` if a problem occurred.
 */
bool gfx_run(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
	}

	SDL_Window* window = SDL_CreateWindow(
		"LTanks",
		0, 0,
		800, 600,
		0 //SDL_WINDOW_RESIZABLE
	);

	if (window == NULL)
	{
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(window);

	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}
