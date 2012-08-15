#!/bin/bash
TARGETS = runtests
VPATH = ../common

all:$(TARGETS)
#FIXME: Manage the dependency on Electric Fence better,
#       so that the code can build on systems without it (in DEBUG mode)
runtests:tests.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
#       -lefence is removed from DEBUG mode as it detected a bug in the GNU regex library
#       Set EF_ALLOW_MALLOC_0=1 in the environment if it is needed to add -lefence back
	gcc -ggdb -DDEBUG -Wall -Werror tests.c ../common/libcleanup.so ../common/libtests.so -o ../runtests
else
	gcc -Wall -Werror tests.c ../common/libcleanup.so ../common/libtests.so -o ../runtests
endif

libcleanup.so:libcleanup.c libcleanup.h
	make -C ../common libcleanup.so
libtests.so:libtests.c libtests.h
	make -C ../common libtests.so

.PHONY:clean
clean:
	-@rm -fvr *~ core* cleanup *.so runtests
.PHONY: rebuild
rebuild:
	make clean all
