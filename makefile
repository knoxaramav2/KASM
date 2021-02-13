#compile all

SUBDIRS = src/graphics src/kasm test

#Options to pass
BITVRS=64
DBGFLAG=-D__DEBUG

export BITVRS
export DBGFLAG

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done