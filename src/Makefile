#makefile for Kampf game engine
CXX = g++
CXXFLAGS = --std=c++0x

LDFLAGS = 

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


#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .cpp .c .hpp .h

.PHONY: all clean kampf tests
kampf: libkampf.a libkampf.so

all: clean kampf tests

%.o: %.cpp %.hpp $(GLOBAL_HPP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

libkampf.a: $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)
	cp $@ $(OUTPUT_DIRECTORY)/

libkampf.so: $(OBJ_FILES)
	$(CXX) -shared $(OBJ_FILES) -o $@ $(CXXFLAGS)
	cp $@ $(OUTPUT_DIRECTORY)/

tests: libkampf.a libkampf.so
	make -C $(TESTS_DIRECTORY)

clean:
	rm -f *.o
	rm -f libkampf.a
	rm -f libkampf.so
	make clean -C $(TESTS_DIRECTORY)
