
CC = g++
CFLAGS = -std=c++17 -Wall -g
LFLAGS = -L../bin -lkasm
DBGFLAGS = -D__DEBUG
OUT = dev
CLEANEXT = o a
BITVRS=64
SRC = launch.cpp
FILE = scripts/dev/graphics.kasm

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../bin/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../bin/
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)$(EXT)
endif

all:
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(DBGFLAGS) \
		$(PLATFORM) $(LFLAGS) -o $(RUNPATH) -lncurses

.PHONY: run
run:
	$(RUNPATH) $(FILE)

.PHONY: clean
clean:
	rm -f $@ *.o
