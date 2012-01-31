#!/bin/bash
all:rename
rename:xlat.c cleanup.sh
	gcc -ggdb xlat.c -o rename
.PHONY:clean
clean:
	@rm -fv *~ rename
.PHONY: rebuild
rebuild:
	make clean all
