#include "gfx_linux/globals.h"
#include "gfx/gfx.h"
#include "gfx_linux/text.h"
#include "game/game.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

static bool g_run;

static void _handle_key(SDL_Event* event)
{
	key_t key;
	if (event->key.keysym.sym == SDLK_ESCAPE)
		key.key = KC_ESCAPE;
	else
		key.key = KC_UNKNOWN;
	game_handle_key(key);
}

/**
 * Handles SDL events.
 */
static void _event_loop(void)
{
	g_run = true;
	while (g_run)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			// Quit the program with either exit-button or ESCAPE.
			if (e.type == SDL_QUIT)
				gfx_quit();
			else if (e.type == SDL_KEYDOWN)
				_handle_key(&e);
			game_step();
			SDL_UpdateWindowSurface(g_window);
		}
	}
}

/**
 * Ends the graphics loop.
 */
void gfx_quit(void)
{
	g_run = false;
}

/**
 * Setup and run graphics.
 *
 * @return `true` normally
 * @return `false` if a problem occurred.
 */
void gfx_run(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        abort();
	}

	g_window = SDL_CreateWindow(
		"LTanks",
		0, 0,
		GFX_CHAR_WIDTH * 9, GFX_CHAR_HEIGHT * 14,
		0 //SDL_WINDOW_RESIZABLE
	);

	if (g_window == NULL)
	{
        SDL_Log("Unable to create window: %s", SDL_GetError());
        abort();
	}
	g_surface = SDL_GetWindowSurface(g_window);

	gfx_init_text();
	SDL_FillRect(g_surface, NULL, SDL_MapRGB(g_surface->format, 0, 0, 0));
	game_loaded();
	_event_loop();

	SDL_DestroyWindow(g_window);
	SDL_Quit();
}
