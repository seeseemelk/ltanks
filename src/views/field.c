#include "views/field.h"
#include "gfx/gfx.h"
#include "game/tank.h"

/*typedef struct
{
	unsigned int width;
	unsigned int height;
} fieldsize_t;*/

static unsigned int offset_x = 1;
static unsigned int offset_y = 1;

static unsigned int field_size()
{
	unsigned int width = gfx_width() - 2 - offset_x;
	unsigned int height = gfx_height() - 2 - offset_y;
	if (width > height)
		return height;
	else
		return width;
}

static unsigned char id_to_char(unsigned int id)
{
	if (id < 10)
		return '0' + id;
	else
		return 'A' + id;
}

void field_show(void)
{
	gfx_clear();
	const unsigned int size = field_size();

	gfx_set_char(0, 0, GFX_TOPLEFT);
	gfx_set_char(size + offset_x, 0, GFX_TOPRIGHT);
	gfx_set_char(0, size + offset_y, GFX_BOTTOMLEFT);
	gfx_set_char(size + offset_x, size + offset_y, GFX_BOTTOMRIGHT);

	for (unsigned int n = 0; n < size; n++)
	{
		gfx_set_char(0, n + offset_y, GFX_VERTICAL);
		gfx_set_char(size + offset_x, n + offset_y, GFX_VERTICAL);

		gfx_set_char(n + offset_x, 0, GFX_HORIZONTAL);
		gfx_set_char(n + offset_x, size + offset_y, GFX_HORIZONTAL);
	}
}

void field_render_tank(Tank tank)
{
	const unsigned int size = field_size() - 1;
	const unsigned int at_x = tank_get_x(tank) / (UINT16_MAX / size) + offset_x;
	const unsigned int at_y = tank_get_y(tank) / (UINT16_MAX / size) + offset_y;
	unsigned char symbol = id_to_char(tank_get_id(tank));
	gfx_set_char(at_x, at_y, symbol);

	float radar = tank_get_radar_direction(tank);
	if (radar < 1*M_PI/8 || radar > 15*M_PI/8)
		gfx_set_char(at_x + 1, at_y, '-');
	else if (radar < 3*M_PI/8)
		gfx_set_char(at_x + 1, at_y + 1, '\\');
	else if (radar < 5*M_PI/8)
		gfx_set_char(at_x, at_y + 1, '|');
	else if (radar < 7*M_PI/8)
		gfx_set_char(at_x - 1, at_y + 1, '/');
	else if (radar < 9*M_PI/8)
		gfx_set_char(at_x - 1, at_y, '-');
	else if (radar < 11*M_PI/8)
		gfx_set_char(at_x - 1, at_y - 1, '\\');
	else if (radar < 13*M_PI/8)
		gfx_set_char(at_x, at_y - 1, '|');
	else
		gfx_set_char(at_x + 1, at_y - 1, '/');
}

void field_render_missile(Missile missile)
{
	const unsigned int size = field_size() - 1;
	const unsigned int at_x = missile_get_x(missile) / (UINT16_MAX / size) + offset_x;
	const unsigned int at_y = missile_get_y(missile) / (UINT16_MAX / size) + offset_y;
	gfx_set_char(at_x, at_y, GFX_CIRCLE);
}


void field_render_explosion(u16 x, u16 y)
{
	const unsigned int size = field_size() - 1;
	const unsigned int at_x = x / (UINT16_MAX / size) + offset_x;
	const unsigned int at_y = y / (UINT16_MAX / size) + offset_y;
	gfx_set_char(at_x, at_y, 2);
}
