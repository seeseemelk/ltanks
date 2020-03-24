#include "game/tank.h"
#include "cdefs.h"
#include <stdlib.h>

struct tank_t
{
	u16 x;
	u16 y;
	u8 cannon_direction;
};

Tank tank_new(void)
{
	Tank tank = malloc(sizeof(struct tank_t));
	tank->x = 0;
	tank->y = 0;
	return tank;
}

void tank_free(Tank tank)
{
	free(tank);
}
