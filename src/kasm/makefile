
CC = g++
CFLAGS = -std=c++17 -Wall -g
LFLAGS = -lm -ldl -lpthread -L../graphics -lkdraw
OUT = libkasm
CLEANEXT = o a
BITVRS=64
DBGFLAG=-D__DEBUG
SUBDIRS=
SRC= defaultInstructions.cpp ops.cpp instructionRegistry.cpp mem.cpp \
	controller.cpp crossplat.cpp debug.cpp utils.cpp \
	
OBJ_FILES = $(SRC:.cpp=.o)
EXPORT_PATH=../../bin/

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=.a
	RUNPATH=./$(EXPEXPORT_PATHORT_PTH)$(OUT)$(EXT)
	TERMLIB=-lncurses
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=.dll
	RUNPATH=$(EXPORT_PATH)$(OUT)$(EXT)
endif

export EXT

%.o : %.cpp
	$(CC) $(CFLAGS) $(LFLAGS) $(DBGFLAG) $(PLATFORM) -c $<

$(RUNPATH): $(OBJ_FILES)
	ar rcs $(EXPORT_PATH)$(OUT)$(EXT) $(OBJ_FILES)

.PHONY: rebuild
rebuild: clean $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
