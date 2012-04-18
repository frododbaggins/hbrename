#!/bin/bash
CLIENT_DIR=/home/mohan/.abc

# TODO: clean this makefile up
all:rename
rename:xlat.c cleanup.sh
ifeq ($(DEBUG),1)
	gcc -ggdb -DDEBUG=1 xlat.c -o rename
else
	gcc xlat.c -o rename
endif
	@chmod a-w rename -v  # make read-only so that 'rm' emits a warning!
perlrename:match.pl
	@cp -f match.pl rename
.PHONY:clean
clean:
	@rm -fvr *~ tests/*~ tests/test-data-files/*~ tests/sanity/*~ tests/basic/*~ tests/pathological/*~ rename
.PHONY: rebuild
rebuild:
	make clean all
.PHONY:release
release:rename cleanup.sh
	-@cp -fv rename $(CLIENT_DIR)/.rename
	-@cp -fv cleanup.sh $(CLIENT_DIR)/.cleanup.sh
