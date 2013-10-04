#makefile for Kampf game engine tests
UNAME := $(shell uname)

CXX = g++
CXXFLAGS = --std=c++0x -m32

LDFLAGS = #-Wl,--verbose

EXEC_EXTENSION = .exe
ifeq ($(UNAME), Linux)
EXEC_EXTENSION =
LDFLAGS += -rdynamic
else
CXXFLAGS += -mwindows
endif

#global hpp files
GLOBAL_HPP= ../kampf.hpp

#get all of the .cpp files and .hpp files
HPP_FILES=$(wildcard *.hpp)
CPP_FILES=$(wildcard *.cpp)
OBJ_FILES=$(CPP_FILES:.cpp=.o)

INC_DIR= -I../ -I./
LIB_DIR= -L../lib -L../ -L./ -LC:\MinGW\lib
LIBS= -lmingw32 -lSDL2main -lSDL2 -lkampf

RUN_SCRIPT = runtests.sh
DELETE_SCRIPT = deletefiles.sh



#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .cpp .c .hpp .h

.PHONY: all clean tests runtests
tests: $(OBJ_FILES)

all: clean tests runtests

%.o: %.cpp $(GLOBAL_HPP)
	$(CXX) $(CXXFLAGS) $(INC_DIR) -o $@ -c $<
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LD_SHARED) -o $* $@ $(LIBS) $(LIB_DIR)
	echo rm -f $* >> $(DELETE_SCRIPT)
	echo $(shell pwd)/$*$(EXEC_EXTENSION) >> $(RUN_SCRIPT)

runtests:
	@test -e $(RUN_SCRIPT) && sh $(RUN_SCRIPT) || \
	echo $(RUN_SCRIPT) does not exist

clean:
	rm -f *.o
	rm -f *.exe
	@test -e $(DELETE_SCRIPT) && sh $(DELETE_SCRIPT) || \
	echo $(DELETE_SCRIPT) does not exist
	rm -f $(DELETE_SCRIPT)
	rm -f $(RUN_SCRIPT)
