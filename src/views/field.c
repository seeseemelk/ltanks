#include "views/field.h"
#include "gfx/gfx.h"
#include "game/tank.h"
#include <stdio.h>

/*typedef struct
{
	unsigned int width;
	unsigned int height;
} fieldsize_t;*/

typedef struct
{
	unsigned int x;
	unsigned int y;
} location_t;

static unsigned int offset_x = 1;
static unsigned int offset_y = 1;

/**
 * Gets the size of the field.
 */
static unsigned int field_size()
{
	unsigned int width = gfx_width() - 2 - offset_x;
	unsigned int height = gfx_height() - 2 - offset_y;
	if (width > height)
		return height;
	else
		return width;
}

/**
 * Converts the ID of a tank to a character.
 */
static unsigned char id_to_char(unsigned int id)
{
	if (id < 10)
		return '0' + id;
	else
		return 'A' + (id - 10);
}

/**
 * Converts a board location to an onscreen location.
 */
static location_t calculate_location(long x, long y)
{
	unsigned int size = field_size();
	location_t location;

	if (x > UINT16_MAX)
		x = UINT16_MAX;
	else if (x < 0)
		x = 0;

	if (y > UINT16_MAX)
		y = UINT16_MAX;
	else if (y < 0)
		y = 0;

	location.x = x / (UINT16_MAX / size) + offset_x;
	location.y = y / (UINT16_MAX / size) + offset_y;
	return location;
}

/**
 * Shows the basic field.
 */
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

/**
 * Renders a tank.
 */
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

/**
 * Renders a missile.
 */
void field_render_missile(Missile missile)
{
	const unsigned int size = field_size() - 1;
	const unsigned int at_x = missile_get_x(missile) / (UINT16_MAX / size) + offset_x;
	const unsigned int at_y = missile_get_y(missile) / (UINT16_MAX / size) + offset_y;
	gfx_set_char(at_x, at_y, GFX_CIRCLE);
}

/**
 * Renders an explosion.
 */
void field_render_explosion(u16 x, u16 y, float radius)
{
	location_t center = calculate_location(x, y);
	location_t start = calculate_location(x - radius, y - radius);
	location_t end = calculate_location(x + radius, y + radius);

	float screen_radius = radius / (UINT16_MAX / field_size());
	float radius_sqr = screen_radius * screen_radius;
	float radius_inner_sqr = radius_sqr / 3.0f;
	float radius_middle_sqr = radius_sqr / 2.0f;

	for (unsigned int at_y = start.y; at_y <= end.y; at_y++)
	{
		for (unsigned int at_x = start.x; at_x <= end.x; at_x++)
		{
			unsigned int dx = absdiff(at_x, center.x);
			unsigned int dy = absdiff(at_y, center.y);
			float distance = dx*dx + dy*dy;
			if (distance <= radius_inner_sqr)
				gfx_set_char(at_x, at_y, GFX_HEAVY);
			else if (distance <= radius_middle_sqr)
				gfx_set_char(at_x, at_y, GFX_MEDIUM);
			else if (distance <= radius_sqr)
				gfx_set_char(at_x, at_y, GFX_LIGHT);
		}
	}
}
