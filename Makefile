# The target can be overridden by either changing this option
# or by passing it on the command line as follows:
# $ TARGET=dos make
TARGET ?= linux
#TARGET ?= dos

BINDIR := bin/$(TARGET)
CFLAGS := -Wall -Wextra -Iincludes -Iincludes/lua -DLTANKS_TARGET=$(TARGET) -DLUA_32BITS
LDFLAGS :=

ifeq ($(TARGET), linux)
EXECUTABLE:=ltanks.linux
DEPS := ncurses
CFLAGS += $(shell pkg-config --cflags $(DEPS)) -MMD -MF $(@:%.o=%.d)
LDFLAGS += $(shell pkg-config --libs $(DEPS))
else ifeq ($(TARGET), dos)
EXECUTABLE:=ltanks.com
CC:=ia16-elf-gcc
endif

include src/Makefile

OBJ=$(SRC:src/%.c=$(BINDIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $< -o $@

$(BINDIR)/%.o: src/%.c
	@mkdir -p $(basename $@)
	$(CC) $(CFLAGS) -MMD -MF $(@:%.o=%.d) -c $< -o $@ -Iincludes

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(EXECUTABLE)

-include $($SRC:src/%.c=$(BINDIR)/%.d)