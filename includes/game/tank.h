#ifndef GAME_TANK_H_
#define GAME_TANK_H_

#include "cdefs.h"

typedef struct tank_t* Tank;

Tank tank_new(void);
void tank_free(Tank tank);
u16 tank_get_x(Tank tank);
u16 tank_get_y(Tank tank);
void tank_set_location(Tank tank, u16 x, u16 y);
void tank_set_motor(Tank tank, float direction, float speed);
void tank_move(Tank tank, float deltatime);

#endif /* GAME_TANK_H_ */
