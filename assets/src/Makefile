# Compiler
CXX := g++

# Executable name
EXEC := main

# Source files
SOURCES := main.cpp player.cpp

# Compiler flags
CXXFLAGS := -std=c++11

# Linker flags
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Build target
all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC) $(LDFLAGS)

# Run target
run: $(EXEC)
	./$(EXEC)

# Clean target
clean:
	rm -f $(EXEC)

# Prevent make from doing something with a file named like a target
.PHONY: all run clean
