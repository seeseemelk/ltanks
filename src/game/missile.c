#include "game/missile.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

struct missile_t
{
	float direction;
	float range_left_sqr;
	u16 x;
	u16 y;
};

Missile missile_new(u16 x, u16 y, float direction, float distance)
{
	Missile missile = malloc(sizeof(struct missile_t));
	missile->direction = direction;
	missile->range_left_sqr = distance * distance;
	missile->x = x;
	missile->y = y;
	return missile;
}

void missile_free(Missile missile)
{
	free(missile);
}

u16 missile_get_x(Missile missile)
{
	return missile->x;
}

u16 missile_get_y(Missile missile)
{
	return missile->y;
}

/**
 * Moves the missile and checks if it has reached it maximum distance.
 *
 * @param missile The missile to move.
 * @return `true` if it hit the ground (reached distance).
 * @return `false` if it is still flying.
 */
bool missile_move(Missile missile)
{
	float dy = (sin(missile->direction) * 1000.0f);
	float dx = (cos(missile->direction) * 1000.0f);
	float distance = dy*dy + dx*dx;

	if ((dy > 0) && (missile->y > UINT16_MAX - dy))
		missile->y = UINT16_MAX;
	else if ((dy < 0) && (missile->y < -dy))
		missile->y = 0;
	else
		missile->y += dy;

	if ((dx > 0) && (missile->x > UINT16_MAX - dx))
		missile->x = UINT16_MAX;
	else if ((dx < 0) && (missile->x < -dx))
		missile->x = 0;
	else
		missile->x += dx;

	missile->range_left_sqr -= distance;
	return missile->range_left_sqr <= 0;
}
