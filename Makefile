#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS=cleanup runtests

all:$(TARGETS)
cleanup:cleanup.c libcleanup.so
ifeq ($(DEBUG),1)
	gcc -Wall -ggdb -DDEBUG cleanup.c libcleanup.so -o cleanup
else
	gcc -Wall cleanup.c libcleanup.so -o cleanup
endif

libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	gcc -c -shared -DDEBUG libcleanup.c -o libcleanup.so
else
	gcc -c -shared libcleanup.c -o libcleanup.so
endif

runtests:tests.c libcleanup.so
	gcc tests.c libcleanup.so -o runtests

.PHONY:clean
clean:
	-@rm -fvr *~ core* cleanup libcleanup.so runtests
.PHONY: rebuild
rebuild:
	make clean all
.PHONY:release
release:cleanup
	-@cp -fv cleanup $(CLIENT_DIR)/.cleanup
