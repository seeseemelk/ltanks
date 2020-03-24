# The target can be overridden by either changing this option
# or by passing it on the command line as follows:
# $ TARGET=dos make
TARGET ?= linux
#TARGET ?= dos

BINDIR := bin/$(TARGET)

ifeq ($(TARGET), linux)
EXECUTABLE:=ltanks.linux
DEPS := ncurses
CC := cc
LD := cc
CFLAGS = -Wall -Wextra \
	-Iincludes -Iincludes/lua \
	-DLTANKS_TARGET=$(TARGET) -DLUA_32BITS \
	-MMD -MF $(@:%.o=%.d) --std=c99 \
	-Wall -Wextra -Werror \
	$(shell pkg-config --cflags $(DEPS)) \
	-c -o $@ $<
LDFLAGS = -lm $(shell pkg-config --libs $(DEPS)) \
	 -o $@ $^

else ifeq ($(TARGET), dos)
EXECUTABLE := ltanks.exe
CC := wcc
LD := wcl
CFLAGS = -os -0 -bc -fpi -Iincludes -Iincludes/lua \
	-ad=$(@:%.o=%.d) -adt=$@ -add=$< \
	-fr=$(@:%.o=%.err) \
	-mm $< -fo=$@ -za99
LDFLAGS = -os -lr -mm -fe=$@ $^
endif

include src/Makefile

OBJ=$(SRC:src/%.c=$(BINDIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

.PHONY: info
info:
	@echo Sources: $(SRC)
	@echo Objects: $(OBJ)
	@echo Binary Directory: $(BINDIR)
	@echo Deps: $(SRC:src/%.c=$(BINDIR)/%.d)

$(EXECUTABLE): $(OBJ)
	$(LD) $(LDFLAGS)

$(BINDIR)/%.o: src/%.c
	@mkdir -p $(basename $@)
	$(CC) $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(EXECUTABLE)

-include $(SRC:src/%.c=$(BINDIR)/%.d)
