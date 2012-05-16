#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS=cleanup runtests

all:$(TARGETS)
cleanup:cleanup.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
	gcc -Wall -ggdb -DDEBUG cleanup.c libtests.so libcleanup.so -o cleanup
else
	gcc -Wall cleanup.c libcleanup.so -o cleanup
endif

libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	gcc -c -shared -DDEBUG libcleanup.c -o libcleanup.so
else
	gcc -c -shared libcleanup.c -o libcleanup.so
endif

libtests.so:libtests.c libtests.h
ifeq ($(DEBUG),1)
	gcc -c -shared -DDEBUG libtests.c -o libtests.so
else
	gcc -c -shared libtests.c -o libtests.so
endif

runtests:tests.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
	gcc -ggdb -DDEBUG tests.c libcleanup.so libtests.so -o runtests
else
	gcc tests.c libcleanup.so libtests.so -o runtests
endif

.PHONY:clean
clean:
	-@rm -fvr *~ core* cleanup *.so runtests
.PHONY: rebuild
rebuild:
	make clean all
.PHONY:release
release:cleanup
	-@cp -fv cleanup $(CLIENT_DIR)/.cleanup
