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
	lua_Number speed = luaL_checknumber(L, 2);

	// Convert to degrees
	lua_Number radians = direction * 180.0 / M_PI;

	// Get VM
	VM vm = lua_touserdata(L, lua_upvalueindex(1));
	Tank tank = vm_get_tank(vm);

	// Set tank parameters
	tank_set_motor(tank, (float) radians, (float) speed);

	// No return arguments
	return 0;
}

static int _api_radar(lua_State* L)
{
	// Get arguments
	lua_Number direction = luaL_checknumber(L, 1);

	// Convert to degrees
	lua_Number radians = direction * 180.0 / M_PI;

	// Get VM
	VM vm = lua_touserdata(L, lua_upvalueindex(1));
	Tank tank = vm_get_tank(vm);

	// Set tank parameters
	tank_set_radar(tank, (float) radians);

	// No return arguments
	return 0;
}

static int _api_fire(lua_State* L)
{
	// Get arguments
	lua_Number direction = luaL_checknumber(L, 1);
	lua_Number distance = luaL_checknumber(L, 2);

	// Convert to degrees
	lua_Number radians = direction * 180.0 / M_PI;

	// Get VM
	VM vm = lua_touserdata(L, lua_upvalueindex(1));
	Tank tank = vm_get_tank(vm);

	// Set tank parameters
	tank_fire(tank, (float) radians, distance);

	// No return arguments
	return 0;
}

static void vm_register(VM vm, lua_State* L, const char* name, lua_CFunction callback)
{
	lua_pushlightuserdata(L, vm);
	lua_pushcclosure(L, callback, 1);
	lua_setglobal(L, name);
}

/**
 * Register library functions for the VM.
 */
void vm_registerlib(VM vm, lua_State* L)
{
	vm_register(vm, L, "move", _api_move);
	vm_register(vm, L, "radar", _api_radar);
	vm_register(vm, L, "fire", _api_fire);
}
