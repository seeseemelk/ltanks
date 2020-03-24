#include "cdefs.h"
#include "game/game.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <stdio.h>

static const char prog[] = "local function main() print(\"Hello\") end main()";

int main(int argc, char** argv)
{
	UNUSED(argc);
	UNUSED(argv);

	game_init();
	game_print_state();

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	if (luaL_dostring(lua, prog) != 0)
	{
		printf("Got an error while running lua code\n");
	}

	lua_close(lua);
	return 0;
}
