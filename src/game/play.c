#include "game/game.h"
#include "game/internal.h"
#include "gfx/gfx.h"

void game_loaded(void)
{
	gfx_print(0, 0, "Hello, world!\nFrom the game...");
}

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
