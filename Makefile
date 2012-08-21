#!/bin/bash
TARGETS=cleanup runtests cscope

VPATH = common src tests
all:$(TARGETS)
cleanup:libcleanup.so cleanup.c
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

libtests.so:libtests.c libtests.h
ifeq ($(DEBUG),1)
	make -C common DEBUG=1 libtests.so
else
	make -C common libtests.so
endif

cscope:cscope.out
cscope.out:cscope.files
	@cscope -b -q -v -k < cscope.files
# If any C source or header files are changed, we have to recreate cscope.files
cscope.files:$(shell find -name "*.[ch]")
	@echo -n "[CSCOPE] "
	@find -name "*.[ch]" > $@
.PHONY:clean
clean:
	-@rm -fvr *~ core* $(TARGETS)
	-@rm -fv lib*.so cscope.*
	make -C src clean
	make -C common clean
	make -C tests clean
.PHONY:cscopeclean
cscopeclean:
	-@rm -fv cscope.*
.PHONY: rebuild
rebuild:
	make clean all cscope
