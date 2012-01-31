#!/bin/bash
CLIENT_DIR=/home/mohan/.abc

# TODO: clean this makefile up and move more into sub-directory makefiles
all:rename
rename:xlat.c cleanup.sh
	gcc -ggdb xlat.c -o rename
.PHONY:clean
clean:
	@rm -fvr *~ tests/*~ tests/test-data-files/*~ tests/sanity/*~ tests/basic/*~ tests/pathological/*~ rename
.PHONY: rebuild
rebuild:
	make clean all
release:
	@cp -fv cleanup.sh $(CLIENT_DIR)
