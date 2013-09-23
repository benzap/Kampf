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

README_FILE=README.md


#replaces .plant with .svg --> foo.plant foo.svg
#creates a list from it
SVGS=$(PLANTS:.plant=.svg)
PNGS=$(PLANTS:.plant=.png)

#redefine our suffixes
.SUFFIXES:
.SUFFIXES: .plant .svg .png

.PHONY: all clean
png : $(PNGS)
svg : $(SVGS)

all: clean svg png

%.svg : %.plant
	$(EXEC) -svg $<
	cp $@ $(OUTPUT_DIRECTORY)

%.png : %.plant
	$(EXEC) $<
	cp $@ $(OUTPUT_DIRECTORY)
	echo '![$@]($@ "$@")' >> $(OUTPUT_DIRECTORY)$(README_FILE)

clean :
	rm -f *.svg
	rm -f $(OUTPUT_DIRECTORY)*.svg
	rm -f *.png
	rm -f $(OUTPUT_DIRECTORY)*.png
	rm -f $(OUTPUT_DIRECTORY)$(README_FILE)

