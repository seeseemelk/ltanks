#ifndef GAME_INTERNAL_H_
#define GAME_INTERNAL_H_

#include "game/game.h"
#include "game/world.h"
#include "vm/vm.h"

struct game_t
{
	World world;
	VM vm;
};

extern struct game_t g_game;

#endif /* GAME_INTERNAL_H_ */
