SRC += $(wildcard src/*.c)

include src/lua/Makefile
include src/game/Makefile
include src/vm/Makefile

ifeq ($(TARGET), linux)
include src/gfx_linux/Makefile
endif