#!/bin/bash
TARGETS:=libcleanup.so libtests.so

all:$(TARGETS)
libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG -std=c99 libcleanup.c -o libcleanup.so
else
	gcc -c -shared libcleanup.c -std=c99 -o libcleanup.so
endif

libtests.so:libtests.c libtests.h
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG -std=c99 libtests.c -o libtests.so
else
	gcc -c -shared libtests.c -std=c99 -o libtests.so
endif

.PHONY:clean
clean:
	-@rm -fv *.so *~