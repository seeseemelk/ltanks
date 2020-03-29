#include "vm/vm.h"
#include "vm/api.h"
#include "game/tank.h"
#include "cdefs.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdlib.h>

struct vm_t
{
	lua_State* luavm;
	Tank tank;
};

/**
 * Frees the Lua state, if one is loaded.
 */
static void vm_free_state(VM vm)
{
	if (vm->luavm != NULL)
		lua_close(vm->luavm);
}

/**
 * Initialises the Lua state.
 */
static void vm_init_state(VM vm)
{
	vm_free_state(vm);
	vm->luavm = luaL_newstate();
	luaL_openlibs(vm->luavm);
	vm_registerlib(vm, vm->luavm);
}

/**
 * Initialises the VM.
 */
VM vm_new(void)
{
	VM vm = malloc(sizeof(struct vm_t));
	vm->luavm = NULL;
	return vm;
}

/**
 * Loads a new VM from a file.
 *
 * @param path Path to the file.
 */
VM vm_new_from_file(const char* path)
{
	VM vm = vm_new();
	vm_init_state(vm);
	if (luaL_loadfile(vm->luavm, path) != LUA_OK)
		abort();
	lua_call(vm->luavm, 0, 0);
	return vm;
}

/**
 * Frees the VM.
 */
void vm_free(VM vm)
{
	vm_free_state(vm);
	free(vm);
}

/**
 * Sets the program that is running on the VM.
 */
bool vm_set_program(VM vm, String program)
{
	vm_init_state(vm);
	return luaL_dostring(vm->luavm, program);
}

/**
 * Sets the tank that is controlled by this program.
 *
 * The VM should either be assigned a new tank or be freed
 * before the tank is freed.
 *
 * @param vm The VM.
 * @param tank The tank.
 */
void vm_set_tank(VM vm, Tank tank)
{
	vm->tank = tank;
}

/**
 * Gets the tank associated to this program.
 *
 * @return The tank associated to this program.
 * @return `NULL` if there is no tank associated.
 */
Tank vm_get_tank(VM vm)
{
	return vm->tank;
}

/**
 * Runs a single iterator of the program.
 */
void vm_run(VM vm)
{
	if (vm->luavm == NULL)
		return;

	lua_getglobal(vm->luavm, "loop");
	lua_call(vm->luavm, 0, 0);
}
