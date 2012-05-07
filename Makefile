#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS=rename perlrename cleanup runtests

all:$(TARGETS)

# The stock C tool (original, uses cleanup.sh for auxiliary work)
rename:xlat.c cleanup.sh
ifeq ($(DEBUG),1)
	gcc -ggdb -DDEBUG=1 xlat.c -o rename
else
	gcc xlat.c -o rename
endif
	@chmod a-w rename  # make read-only so that 'rm' emits a warning!

# Perl version of the rename tool
perlrename:match.pl
	@cp -fv match.pl perlrename
	@chmod a-w perlrename  # make read-only so that 'rm' emits a warning!

# The integrated version (in C). This does not use cleanup.sh
# for safety checks and directory walking.
cleanup:cleanup.c libcleanup.so
ifeq ($(DEBUG),1)
	gcc -Wall -ggdb -DDEBUG cleanup.c libcleanup.so -o cleanup
else
	gcc -Wall cleanup.c libcleanup.so -o cleanup
endif

libcleanup.so:libcleanup.c libcleanup.h
	gcc -c -shared libcleanup.c -o libcleanup.so

runtests:tests.c libcleanup.so
	gcc tests.c libcleanup.so -o runtests

.PHONY:clean
clean:
	-@rm -fvr *~ rename perlrename core* cleanup libcleanup.so
	-@rm -fvr *~ tests/*~ tests/sanity/*~ tests/basic/*~ tests/pathological/*~
.PHONY: rebuild
rebuild:
	make clean all
.PHONY:release
release:rename cleanup.sh
	-@cp -fv rename $(CLIENT_DIR)/.rename
	-@cp -fv cleanup.sh $(CLIENT_DIR)/.cleanup.sh
.PHONY:perlrelease
	-@cp -fv perlrename $(CLIENT_DIR)/.rename
	-@cp -fv cleanup.sh $(CLIENT_DIR)/.cleanup.sh
