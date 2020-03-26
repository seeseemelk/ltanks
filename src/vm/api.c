#include "vm/api.h"
#include "vm/vm.h"
#include "game/tank.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "cdefs.h"

static int _api_move(lua_State* L)
{
	// Get arguments
	lua_Number direction = luaL_checknumber(L, 1);
	lua_Number speed = luaL_checknumber(L, 1);

	// Convert to degrees
	direction *= 180.0 / M_PI;

	// Get VM
	VM vm = lua_touserdata(L, lua_upvalueindex(1));
	Tank tank = vm_get_tank(vm);

	// Set tank parameters
	tank_set_motor(tank, (float) direction, (float) speed);

	// No return arguments
	return 0;
}

/**
 * Register library functions for the VM.
 */
void vm_registerlib(VM vm, lua_State* L)
{
	lua_pushlightuserdata(L, vm);
	lua_pushcclosure(L, _api_move, 1);
	lua_setglobal(L, "move");
}
