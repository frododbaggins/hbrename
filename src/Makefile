#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS=cleanup runtests

VPATH = ../common

all:$(TARGETS)
#FIXME: Manage the dependency on Electric Fence better,
#       so that the code can build on systems without it (in DEBUG mode)
cleanup:cleanup.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
	gcc -Wall -Werror -ggdb -DDEBUG -lefence cleanup.c ../common/libtests.so ../common/libcleanup.so -o ../cleanup
else
	gcc -Wall -Werror cleanup.c ../common/libcleanup.so -o ../cleanup
endif

libcleanup.so:
ifeq ($(DEBUG),1)
	make -C ../common DEBUG=1 libcleanup.so
else
	make -C ../common libcleanup.so
endif

libtests.so:
ifeq ($(DEBUG),1)
	make -C ../common DEBUG=1 libtests.so
else
	make -C ../common libtests.so
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
