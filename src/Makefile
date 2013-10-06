#makefile for Kampf game engine
UNAME := $(shell uname)

CXX = g++
CXXFLAGS = --std=c++0x

LDFLAGS = #-Wl,--verbose

LD_STATIC = -static
LD_SHARED = -shared

ifeq ($(UNAME), Linux)
CXXFLAGS += -fPIC -DKF_LINUX
else
CXXFLAGS += -mwindows -m32 -DKF_WIN
endif

#directory where the output will be placed
OUTPUT_DIRECTORY = ../lib
#tests include
TESTS_DIRECTORY = ./tests

#global hpp files
GLOBAL_HPP= KF_globals.hpp KF_utilities.hpp

#get all of the .cpp files and .hpp files
HPP_FILES=$(wildcard *.hpp)
CPP_FILES=$(wildcard *.cpp)
OBJ_FILES=$(CPP_FILES:.cpp=.o)

ifeq ($(UNAME), Linux)
LIBS = -lSDL2main -lSDL2 
else
LIBS = -lmingw32 -lSDL2main -lSDL2 
endif

LIBS_DIR= -L. -L../lib -LC:\MinGW\lib

#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .cpp .c .hpp .h

.PHONY: all clean kampf tests runtests
kampf: libkampf.a libkampf.so

all: clean kampf tests

%.o: %.cpp %.hpp $(GLOBAL_HPP)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS_DIR) $(LIBS) 

libkampf.a: $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)
	cp $@ $(OUTPUT_DIRECTORY)/

libkampf.so: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LD_SHARED) -o $@ $(OBJ_FILES) $(LIBS_DIR) $(LIBS) 
	cp $@ $(OUTPUT_DIRECTORY)/
	cp $@ $(TESTS_DIRECTORY)/
runtests:
	make runtests -C $(TESTS_DIRECTORY)

tests: libkampf.a libkampf.so
	make -C $(TESTS_DIRECTORY)

clean:
	rm -f *.o
	rm -f libkampf.a
	rm -f libkampf.so
	rm -f $(OUTPUT_DIRECTORY)/libkampf.a
	rm -f $(OUTPUT_DIRECTORY)/libkampf.so
	rm -f $(TESTS_DIRECTORY)/libkampf.so
	make clean -C $(TESTS_DIRECTORY)
