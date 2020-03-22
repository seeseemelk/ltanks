#include "utils.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <stdio.h>

static const char prog[] = "local function main() print(\"Hello\") end main()";

int main(int argc, char** argv)
{
	lua_State *lua;
	UNUSED(argc);
	UNUSED(argv);

	lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_dostring(lua, prog);

	lua_close(lua);
	return 0;
}
