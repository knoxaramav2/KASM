#Render or configure program

CC = g++
CFLAGS = -std=c++14 -Wall -g
LFLAGS = -lm -ldl -lpthread
OUT = dev
CLEANEXT = o a
BITVRS=64
DBGFLAG=-D__DEBUG
SRC= launch.cpp

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../bin/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
	TERMLIB=-lncurses
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
	$(CC) $(SRC) $(OSMODE) $(DBGFLAG) $(CFLAGS) $(PLATFORM) $(LFLAGS) $(TERMLIB) -o $(RUNPATH)

.PHONY: run
run:
	$(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
