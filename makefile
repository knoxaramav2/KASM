#compile KNX library
#OUT = libKNX_Library$(LIB_EXT)

#SRC = strutil.c hash.c tree.c filestr.c console_io.c console.c \
	win_console.c unix_console.c
#DIRS := $(wildcard */.)
#GARBAGE := $(foreach DIR, $(DIRS), $(DIR)/$(CLEAN_TEXT))

#OBJ_FILES = $(SRC:.c=.o)
#current_dir = $(shell pwd)

#%.o : %.c
#	$(CC) $(INCLUDES) $(COMMON) -c $<

#$(EXPORT_PATH)$(OUT): $(OBJ_FILES)
#	ar rcs $(EXPORT_PATH)$(OUT) $(OBJ_FILES)

#.PHONY: clean
#clean:
#	rm -f $@ *.o


#Render or configure program

CC = g++
CFLAGS = -std=c++14 -Wall -g
LFLAGS = -lm -ldl -lpthread
OUT = kasm
CLEANEXT = o a
BITVRS=64
DBGFLAG=-D__DEBUG
SRC= main.cpp
OBJ_FILES = $(SRC:.cpp=.o)


ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PATH=./bin/
	EXT=
	RUNPATH=./$(EXPEXPORT_PATHORT_PTH)$(OUT)$(EXT)
	TERMLIB=-lncurses
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PATH=./bin/
	EXT=.exe
	RUNPATH=$(EXPORT_PATH)$(OUT)$(EXT)
endif

%.o : %.cpp
	$(CC) -c $<

$(RUNPATH): $(OBJ_FILES)
	ar rcs $(EXPORT_PATH)$(OUT) $(OBJ_FILES)

#all:
#	$(CC) $(SRC) $(OSMODE) $(DBGFLAG) $(CFLAGS) $(PLATFORM) $(LFLAGS) $(TERMLIB) -o $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
