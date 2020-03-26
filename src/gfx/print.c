#include "gfx/gfx.h"
#include <stdbool.h>

/**
 * Prints a line.
 *
 * It will convert certain characters (such as `\n`). If the
 * graphical characters is needed instead, prefix with either
 * `\xFF` or use `gfx_set_char`.
 */
void gfx_print(unsigned int x, unsigned int y, const char* str)
{
	unsigned int original_x = x;
	bool force_print = false;

	while (*str != 0)
	{
		if (force_print)
		{
			gfx_set_char(x, y, *str);
			++x;
		}
		else
		{
			switch (*str)
			{
			case '\n':
				x = original_x;
				y++;
				break;
			case '\xFF':
				force_print = true;
				break;
			default:
				gfx_set_char(x, y, *str);
				++x;
				break;
			}
		}

		++str;
	}
}
