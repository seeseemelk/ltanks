#ifndef VM_API_H_
#define VM_API_H_

#include "vm/vm.h"
#include "lua.h"

void vm_registerlib(VM vm, lua_State* L);

#endif /* VM_API_H_ */
