OUT := ${shell pwd}/out

.PHONY: all clean

all:
	make -f build/Makefile.server all
	make -f build/Makefile.client all

clean:
	@rm -rf ${OUT} > /dev/null
