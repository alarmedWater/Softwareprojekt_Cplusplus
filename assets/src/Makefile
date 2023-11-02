# Compiler
CXX := g++

# Executable name
EXEC := main

# Source files
SOURCES := main.cpp player.cpp level.cpp

# Object files directory
OBJDIR := obj

# Object files
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(addprefix $(OBJDIR)/,$(OBJECTS))

# Compiler flags
CXXFLAGS := -std=c++11

# Include directories
INCLUDES := -I./ -I/usr/include/SFML/include

# Linker flags
LDFLAGS := -L/usr/include/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

# Build target
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Rule to make object files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run target
run: $(EXEC)
	./$(EXEC)

# Clean target
clean:
	rm -f $(EXEC)
	rm -rf $(OBJDIR)

# Prevent make from doing something with a file named like a target
.PHONY: all run clean
