#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS=rename perlrename cleanup

all:$(TARGETS)
rename:xlat.c cleanup.sh
ifeq ($(DEBUG),1)
	gcc -ggdb -DDEBUG=1 xlat.c -o rename
else
	gcc xlat.c -o rename
endif
	@chmod a-w rename  # make read-only so that 'rm' emits a warning!
perlrename:match.pl
	@cp -fv match.pl perlrename
	@chmod a-w perlrename  # make read-only so that 'rm' emits a warning!
.PHONY:clean
clean:
	-@rm -fvr *~ tests/*~ tests/sanity/*~ tests/basic/*~ tests/pathological/*~ rename perlrename core* cleanup
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
cleanup:
	gcc -Wall -ggdb cleanup.c -o cleanup