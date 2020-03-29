#ifndef VM_VM_H_
#define VM_VM_H_

#include "game/types.h"
#include "cdefs.h"
#include <stdbool.h>

typedef struct vm_t* VM;

VM vm_new(void);
VM vm_new_from_file(const char* path);
void vm_free(VM vm);

bool vm_set_program(VM vm, String program);
void vm_set_tank(VM vm, Tank tank);
Tank vm_get_tank(VM vm);
void vm_run(VM vm);

#endif /* VM_VM_H_ */
