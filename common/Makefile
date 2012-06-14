#!/bin/bash
TARGETS:=libcleanup.so libtests.so

all:$(TARGETS)
#FIXME: Manage the dependency on Electric Fence better,
#       so that the code can build on systems without it (in DEBUG mode)
libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG -std=c99 -lefence libcleanup.c -o libcleanup.so
else
	gcc -c -shared libcleanup.c -std=c99 -o libcleanup.so
endif

libtests.so:libtests.c libtests.h test-input-data
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG -std=c99 -lefence libtests.c -o libtests.so
else
	gcc -c -shared libtests.c -std=c99 -o libtests.so
endif

.PHONY:clean
clean:
	-@rm -fv *.so *~