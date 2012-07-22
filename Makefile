#!/bin/bash
TARGETS=cleanup runtests

VPATH = common src tests
all:$(TARGETS)
cleanup:
ifeq ($(DEBUG),1)
	make -C src DEBUG=1 cleanup
else
	make -C src cleanup
endif

runtests:tests.c libcleanup.so libtests.so
ifeq ($(DEBUG),1)
	make -C tests DEBUG=1 runtests
else
	make -C tests runtests
endif

libcleanup.so:libcleanup.c libcleanup.h
ifeq ($(DEBUG),1)
	make -C common DEBUG=1 libcleanup.so
else
	make -C common libcleanup.so
endif

libtests.so:libtests.c libtests.h test-input-data
ifeq ($(DEBUG),1)
	make -C common DEBUG=1 libtests.so
else
	make -C common libtests.so
endif

.PHONY:clean
clean:
	-@rm -fvr *~ core* $(TARGETS)
	-@rm -fv lib*.so
	make -C src clean
	make -C common clean
	make -C tests clean
.PHONY: rebuild
rebuild:
	make clean all
