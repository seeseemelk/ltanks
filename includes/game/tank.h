#ifndef GAME_TANK_H_
#define GAME_TANK_H_

#include "cdefs.h"

typedef struct tank_t* Tank;

Tank tank_new(void);
void tank_free(Tank tank);
u16 tank_get_x(Tank tank);
u16 tank_get_y(Tank tank);
void tank_move(Tank tank, u16 x, u16 y);

#endif /* GAME_TANK_H_ */
