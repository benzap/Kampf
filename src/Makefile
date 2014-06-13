#makefile for Kampf game engine
UNAME := $(shell uname)

TAGS_EXEC = etags

CXX = g++
CXXFLAGS = --std=c++0x

LDFLAGS = #-Wl,--verbose

LD_STATIC = -static-libgcc -static-libstdc++ #-static
LD_SHARED = -shared

BUILD = debug

#Production Build Versus Debug Build
ifeq ($(BUILD), production)
CXXFLAGS += -O2
else ifeq ($(BUILD), debug)
CXXFLAGS += -g
else
echo "Warning: Build Parameter is incorrect, using default debug build"
CXXFLAGS += -g
endif

ifeq ($(UNAME), Linux)
CXXFLAGS += -fPIC -DKF_LINUX
else
CXXFLAGS += -mconsole -m32 -DKF_WIN
endif


#directory holding any helpful scripts
SCRIPTS_DIRECTORY = ../scripts
#the binary directory for DLL-like libraries
BIN_DIRECTORY = ../bin
#directory where the resulting includes should be placed
INCLUDES_DIRECTORY = ../include/kampf/
#directory where the output will be placed
OUTPUT_DIRECTORY = ../lib
#tests include
TESTS_DIRECTORY = ./tests

#global hpp files
GLOBAL_HPP= KF_globals.hpp KF_utilities.hpp KF_math.hpp

#included directories considered for compiling
INCLUDED_DIRS = ./collision ./physics

#get all of the .cpp files and .hpp files
HPP_FILES = $(wildcard *.hpp)
HPP_FILES += $(foreach dir,$(INCLUDED_DIRS),$(wildcard $(dir)/*.hpp))
CPP_FILES = $(wildcard *.cpp)
CPP_FILES += $(foreach dir,$(INCLUDED_DIRS),$(wildcard $(dir)/*.cpp))
OBJ_FILES = $(CPP_FILES:.cpp=.o)

#Libraries
LIBS = 
ifeq ($(UNAME), Linux)
LIBS += -lSDL2main -lSDL2 -lluajit-5.1 -lSDL2_ttf -lSDL2_image
else
LIBS += -lmingw32 -lSDL2main -lSDL2 -lShlwapi -llua51 -lSDL2_ttf -lSDL2_image
endif

#Library Directories
LIBS_DIR= -L. -L../lib -LC:\MinGW\lib

#Include Directories
INC_DIR = -I./ -I../
ifeq ($(UNAME), Linux)
INC_DIR +=
else
INC_DIR += 
endif

#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .cpp .c .hpp .h

.PHONY: all clean kampf tests runtests tags
kampf: libkampf.a libkampf.so
	mkdir -p $(INCLUDES_DIRECTORY)
	cp ./*.hpp $(INCLUDES_DIRECTORY)/
	mkdir -p $(INCLUDES_DIRECTORY)/physics
	cp ./physics/*.hpp $(INCLUDES_DIRECTORY)/physics/
	mkdir -p $(INCLUDES_DIRECTORY)/collision
	cp ./collision/*.hpp $(INCLUDES_DIRECTORY)/collision/
	mkdir -p $(SCRIPTS_DIRECTORY)
	cp ./scripts/*.lua  $(SCRIPTS_DIRECTORY)

all: clean kampf tests

%.o: %.cpp %.hpp $(GLOBAL_HPP)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS_DIR) $(LIBS) $(INC_DIR)

######### INCLUDED DIRECTORIES #############
./collision/%.o: ./collision/%.cpp ./collision/%.hpp $(GLOBAL_HPP)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS_DIR) $(LIBS) $(INC_DIR)

./physics/%.o: ./physics/%.cpp ./physics/%.hpp $(GLOBAL_HPP)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS_DIR) $(LIBS)
#############################################


libkampf.a: $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)
	cp $@ $(OUTPUT_DIRECTORY)/

libkampf.so: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LD_SHARED) -o $@ $(OBJ_FILES) $(LIBS_DIR) $(LIBS) 
	cp $@ $(OUTPUT_DIRECTORY)/
	cp $@ $(TESTS_DIRECTORY)/
	cp $@ $(BIN_DIRECTORY)/
runtests:
	make runtests -C $(TESTS_DIRECTORY)

tests: libkampf.a libkampf.so
	make -C $(TESTS_DIRECTORY)

clean:
	rm -f $(OBJ_FILES)
	rm -f libkampf.a
	rm -f libkampf.so
	rm -f $(OUTPUT_DIRECTORY)/libkampf.a
	rm -f $(OUTPUT_DIRECTORY)/libkampf.so
	rm -f $(TESTS_DIRECTORY)/libkampf.so
	rm -rf $(BIN_DIRECTORY)/*
	rm -rf $(SCRIPTS_DIRECTORY)/*
	rm -rf $(INCLUDES_DIRECTORY)/*
	make clean -C $(TESTS_DIRECTORY)

#generate TAGS file
tags:
	make -C $(TESTS_DIRECTORY) tags TAGS_EXEC=$(TAGS_EXEC)
	$(TAGS_EXEC) $(HPP_FILES) $(CPP_FILES) --include=$(TESTS_DIRECTORY)/TAGS
