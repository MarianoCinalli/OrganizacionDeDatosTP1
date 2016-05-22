# Variables

 SOURCES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
 TEMP := $(subst src/,obj/,$(SOURCES))
 OBJECTS := $(subst .cpp,.o,$(TEMP))
 LINKING_FLAGS := -Wall -I headers/ -o
 COMPILING_FLAGS := -Wall -I headers/ -c -o

# Target

 main: $(OBJECTS)
	g++ $(LINKING_FLAGS) $@ $^

# Pattern

 obj/%.o: src/%.cpp
	g++ $(COMPILING_FLAGS) $@ $<

# Clean object files and binary

 clean:
	rm -f $(OBJECTS)
	rm -f main
