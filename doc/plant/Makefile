#plant uml directory ex. /home/plantumlfolder/
PLANTUML_ROOT= 
#directory which will be scraped of .plant files
PLANTS_DIRECTORY =
#directory where the output will be placed
OUTPUT_DIRECTORY = ../


PLANTUML_EXEC = plantuml.jar
#java root, should be in your PATH anyways
JAVA_ROOT = 
JAVA_EXEC = java

# executed command java -jar plantuml.jar
EXEC=$(JAVA_ROOT)$(JAVA_EXEC) -jar $(PLANTUML_ROOT)$(PLANTUML_EXEC)

#get all of the .plant files
PLANTS=$(wildcard $(PLANTS_DIRECTORY)*.plant)
SVGS=$(PLANTS:.plant=.svg)
PNGS=$(PLANTS:.plant=.png)

#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .plant .svg .png

.PHONY: all clean

all: svg png

svg : $(SVGS)
png : $(PNGS)

%.svg : %.plant
	$(EXEC) -svg $<
# TODO: causes stackdump in windows
#	cp $@ $(OUTPUT_DIRECTORY)

%.png : %.plant
	$(EXEC) $<
# TODO: causes stackdump in windows
#	cp $@ $(OUTPUT_DIRECTORY)

clean :
# TODO: causes stackdump in windows
#	rm -f *.svg
#	rm -f *.png
	@echo "Warning: removing SVGs and PNGs causes stackdump in windows"
