#include "game/game.h"
#include "game/internal.h"
#include "gfx/gfx.h"
#include "views/field.h"
#include <stdlib.h>

/**
 * Executed when the game is loaded.
 */
void game_loaded(void)
{
	gfx_print(0, 0, "Hello, world!\nFrom the game...");
}

/**
 * Handles a single key press.
 */
void game_handle_key(key_t key)
{
	switch (key.key)
	{
	case KC_ESCAPE:
		gfx_quit();
		break;
	case KC_UNKNOWN:
		break;
	}
}

/**
 * Runs a single step of the game.
 */
void game_step(void)
{
	// Run VM state
	vm_run(g_game.vm);

	// Move and render all tanks
	range_t iterator = world_get_tanks(g_game.world);
	Tank tank;

	field_show();
	while ((tank = range_next(&iterator)) != NULL)
	{
		tank_move(tank, 1.0f);
		field_show_tank(tank);
	}
}
