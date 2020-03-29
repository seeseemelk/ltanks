# The target can be overridden by either changing this option
# or by passing it on the command line as follows:
# $ TARGET=dos make
TARGET ?= linux
#TARGET ?= dos

BINDIR := bin/$(TARGET)

ifeq ($(TARGET), linux)
EXECUTABLE:=ltanks.linux
DEPS := sdl2
CC := cc
LD := cc
CFLAGS = -Wall -Wextra \
	-Iincludes -Iincludes/lua \
	-DLTANKS_TARGET=$(TARGET) -DLUA_32BITS \
	-MMD -MF $(@:%.o=%.d) --std=c99 \
	-Wall -Wextra -Werror -ggdb \
	$(shell pkg-config --cflags $(DEPS)) \
	-c -o $@ $<
LDFLAGS = -lm $(shell pkg-config --libs $(DEPS)) \
	 -o $@ $^

else ifeq ($(TARGET), dos)
export INCLUDE=$(WATCOM)/h
EXECUTABLE := ltanks.exe
CC := wcl
LD := wcl
CFLAGS = -c -os -0 -bc -Iincludes -Iincludes/lua \
	-ad=$(@:%.o=%.d) -adt=$@ -add=$< \
	-fr=$(@:%.o=%.err) \
	-mm $< -fo=$@ -za99 -fpi87 \
	-bcl=dos
LDFLAGS = -os -0 -om -lr -mm -fe=$@ $^
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

.PHONY: docs
docs:
	doxygen

$(EXECUTABLE): $(OBJ)
	$(LD) $(LDFLAGS)

$(BINDIR)/%.o: src/%.c
	@mkdir -p $(basename $@)
	$(CC) $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(EXECUTABLE)

%.h:
	
-include $(SRC:src/%.c=$(BINDIR)/%.d)
