#makefile for Kampf game engine
CXX = g++
CXXFLAGS = --std=c++0x

LDFLAGS = 

#global hpp files
GLOBAL_HPP= ../kampf.hpp

#get all of the .cpp files and .hpp files
HPP_FILES=$(wildcard *.hpp)
CPP_FILES=$(wildcard *.cpp)
OBJ_FILES=$(CPP_FILES:.cpp=.o)

INC_DIR= -I../
LIB_DIR= -L../
LIBS= -lkampf

DELETE_SCRIPT = deletefiles.sh

#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .cpp .c .hpp .h

.PHONY: all clean tests runtests
all: tests

%.o: %.cpp $(GLOBAL_HPP)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INC_DIR) $(LIB_DIR) $(LIBS)
	$(CXX) $@ -o $* $(CXXFLAGS) $(INC_DIR) $(LIB_DIR) $(LIBS)
	echo rm -f $* >> $(DELETE_SCRIPT)

tests: $(OBJ_FILES)

clean:
	rm -f *.o
	rm -f *.exe
	@test -e $(DELETE_SCRIPT) && sh $(DELETE_SCRIPT) || \
	echo $(DELETE_SCRIPT) does not exist
	rm -f $(DELETE_SCRIPT)
