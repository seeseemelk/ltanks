#include "gfx/gfx.h"
#include "game/game.h"
#include "cdefs.h"
#include <stdbool.h>
#include <graph.h>
#include <conio.h>
#include <dos.h>

static bool g_run;

static void _handle_special(char key)
{
	switch (key)
	{
	default:
		break;
	}
}

static void _handle_normal(char key)
{
	key_t event;
	switch (key)
	{
	case 0x1B:
		event.key = KC_ESCAPE;
		break;
	default:
		event.key = KC_UNKNOWN;
		break;
	}
	game_handle_key(event);
}

void gfx_run(void)
{
	_setvideomode(_TEXTMONO);
	_clearscreen(_GCLEARSCREEN);
	_displaycursor(false);

	g_run = true;
	game_loaded();

	int page_to_use = 0;

	while (g_run)
	{
		_setactivepage(page_to_use);
		if (_kbhit() != 0)
		{
			int c = _getch();
			if (c == 0)
				_handle_special(_getch());
			else
				_handle_normal(c);
		}

		if (game_step())
		{
			_setvisualpage(page_to_use);
			page_to_use = 1 - page_to_use;
		}
	}
}

void gfx_quit(void)
{
	g_run = false;
}

void gfx_set_char(unsigned int x, unsigned int y, unsigned char c)
{
	unsigned char str[2];
	str[0] = c;
	str[1] = 0;

	_settextposition(y + 1, x + 1);
	_outtext(str);
}

void gfx_clear(void)
{
	_clearscreen(_GCLEARSCREEN);
}

unsigned int gfx_width(void)
{
	return 80;
}

unsigned int gfx_height(void)
{
	return 25;
}
