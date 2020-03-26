SRC += $(wildcard src/*.c)

include src/lua/Makefile
include src/game/Makefile
include src/vm/Makefile
include src/views/Makefile
include src/gfx/Makefile

ifeq ($(TARGET), linux)
include src/gfx_linux/Makefile
else ifeq ($(TARGET), dos)
include src/gfx_dos/Makefile
endif