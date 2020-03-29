#ifndef GAME_INTERNAL_H_
#define GAME_INTERNAL_H_

#include "game/game.h"
#include "game/world.h"
#include "vm/vm.h"
#include "array.h"

struct game_t
{
	World world;
	Array vm;
	unsigned int next_bot_id;
};

extern struct game_t g_game;

#endif /* GAME_INTERNAL_H_ */
