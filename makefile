# Variables

 SOURCES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
 TEMP := $(subst src/,obj/,$(SOURCES))
 OBJECTS := $(subst .cpp,.o,$(TEMP))
 LINKING_FLAGS := -std=c++11 -Wall -I headers/ -o
 COMPILING_FLAGS := -std=c++11 -Wall -I headers/ -c -o
 
 MKDIR_P := xargs mkdir -p <dirs.txt

# Target
 all: directories main

 main: $(OBJECTS)
	g++ $(LINKING_FLAGS) $@ $^

 directories: 
	${MKDIR_P}

# Pattern

 obj/%.o: src/%.cpp
	g++ $(COMPILING_FLAGS) $@ $<

# Clean object files and binary

 clean:
	rm -f $(OBJECTS)
	rm -f main

.PHONY: all clean main

# copy find ./src -type d >dirs.txt
# paste xargs mkdir -p <dirs.txt^C



