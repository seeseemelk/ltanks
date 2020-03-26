#include "views/field.h"
#include "gfx/gfx.h"
#include "game/tank.h"

static unsigned int _field_size()
{
	unsigned int width = gfx_width();
	unsigned int height = gfx_height();
	if (width > height)
		return height;
	else
		return width;
}

void field_show(void)
{
	gfx_clear();
	for (int y = 0; y < 16; y++)
		for (int x = 0; x < 16; x++)
		{
			gfx_set_char(x, y, (y<<4)|x);
		}
}

void field_show_tank(Tank tank)
{
	unsigned int size = _field_size();
	unsigned int at_x = tank_get_x(tank) / (UINT16_MAX / size);
	unsigned int at_y = tank_get_y(tank) / (UINT16_MAX / size);
	gfx_set_char(at_x, at_y, 'O');
}
