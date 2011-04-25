#Makefile for Kampf
#Written By: Benjamin Zaporzan
ProgramName:= Kampf
CPP:= g++

#dealing with the source code
SOURCE_DIR:=./
FILES:= $(wildcard $(SOURCE_DIR)/*.cpp)
FILES:= $(notdir $(FILES))

#dealing with objects
OBJECTS:=  $(patsubst %.cpp, %.o, $(FILES))

#dealing with libraries
LIBRARY_DIR:= -L../libs
LIBRARIES:= -lGL -lGLU -lsfml-window

#dealing with includes
INCLUDES_DIR:= -I../includes
GLOBE_HEADERS:= kampf_general.hpp

#dealing with debug flags and debugging
DEBUG_FLAGS:= -g

#My objs

%.o : %.cpp %.hpp $(GLOBE_HEADERS)
	$(CPP) -c $(INCLUDES_DIR) $(LIBRARIES) $(LIBRARY_DIR) $< -o $@ $(DEBUG_FLAGS)

kampf : $(OBJECTS) $(GLOBE_HEADERS)
	$(CPP) $(LIBRARIES) $(OBJECTS) $(INCLUDES_DIR) -o ../$(ProgramName) $(DEBUG_FLAGS)


#big fat .PHONY's

.PHONY: clean
clean:
	rm -f $(ProgramName) $(OBJECTS_DIR)/*.o $(SOURCE_DIR)/*.o


