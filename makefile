#compile all

SUBDIRS = src/graphics src/kasm test
CLEANDIRS = $(SUBDIRS) bin

#Options to pass
BITVRS=64
DBGFLAG=-D__DEBUG
OSMODE = -DBITMODE=$(BITVRS)
CLEANEXT = o a dll exe

FILE = scripts/dev/conditionals.kasm

ifeq ($(shell uname), Linux)
	PLATFORM = -D__LINUX
	EXT=
	LIBEXT=
else
#Windows
	PLATFORM = -D__WINDOWS
	EXT=.exe
	LIBEXT=.dll
endif

export BITVRS
export DBGFLAG
export OSMODE
export PLATFORM
export EXT
export CLEANEXT

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir clean; \
	done

.PHONY: run
run:
	./bin/dev$(EXT) $(FILE)
