#!/bin/bash
TARGETS:=libcleanup.so libtests.so

all:$(TARGETS)
libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG libcleanup.c -o libcleanup.so
else
	gcc -c -shared libcleanup.c -o libcleanup.so
endif

libtests.so:libtests.c libtests.h
ifeq ($(DEBUG),1)
	gcc -c -shared -ggdb -DDEBUG libtests.c -o libtests.so
else
	gcc -c -shared libtests.c -o libtests.so
endif

.PHONY:clean
clean:
	-@rm -fv *.so *~