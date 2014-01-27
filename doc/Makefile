#makefile for generating documentation

#tool used to generate documentation
DOC_EXEC= doxygen

#root directory of the src code
SRC_ROOT= ../src

#redefine our suffixes
.SUFFIXES:

.PHONY: all clean docs

all: docs clean

docs:
	make -f ./plant/Makefile
	$(DOC_EXEC)
