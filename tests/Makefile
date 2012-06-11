#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
TARGETS = runtests
VPATH = ../common

all:$(TARGETS)
#FIXME: Manage the dependency on Electric Fence better,
#       so that the code can build on systems without it (in DEBUG mode)
runtests:tests.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
	gcc -ggdb -DDEBUG -lefence tests.c ../common/libcleanup.so ../common/libtests.so -o ../runtests
else
	gcc tests.c ../common/libcleanup.so ../common/libtests.so -o ../runtests
endif

libcleanup.so:
	make -C ../common libcleanup.so
libtests.so:
	make -C ../common libtests.so

.PHONY:clean
clean:
	-@rm -fvr *~ core* cleanup *.so runtests
.PHONY: rebuild
rebuild:
	make clean all
.PHONY:release
release:cleanup
	-@cp -fv cleanup $(CLIENT_DIR)/.cleanup
