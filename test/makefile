
CC = g++
CFLAGS = -std=c++14 -Wall -g
LFLAGS = -L../bin -lkasm
OUT = dev
CLEANEXT = o a
BITVRS=64
SRC= launch.cpp

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
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) \
		$(PLATFORM) $(LFLAGS) -o $(RUNPATH)

.PHONY: run
run:
	$(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o
