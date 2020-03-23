# The target can be overridden by either changing this option
# or by passing it on the command line as follows:
# $ TARGET=dos make
TARGET ?= linux
#TARGET ?= dos

BINDIR := bin/$(TARGET)

ifeq ($(TARGET), linux)
EXECUTABLE:=ltanks.linux
DEPS := ncurses
CFLAGS := -Wall -Wextra \
	-Iincludes -Iincludes/lua \
	-DLTANKS_TARGET=$(TARGET) -DLUA_32BITS -MMD -MF $(@:%.o=%.d) \
	$(shell pkg-config --cflags $(DEPS)) \
	-c
LDFLAGS += -lm $(shell pkg-config --libs $(DEPS))

else ifeq ($(TARGET), dos)
EXECUTABLE := ltanks.exe
CC := wcc
CFLAGS := -os -0 -bc -fpi -Iincludes -Iincludes/lua -mm
LDFLAGS += -os -lr -mm
endif

include src/Makefile

OBJ=$(SRC:src/%.c=$(BINDIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	wcl $^ $(LDFLAGS) -fe=$@
#	$(CC) $^ $(LDFLAGS) -o $@

$(BINDIR)/%.o: src/%.c
	@mkdir -p $(basename $@)
	$(CC) $(CFLAGS) $< -fo=$@

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(EXECUTABLE)

-include $($SRC:src/%.c=$(BINDIR)/%.d)
