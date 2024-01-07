# Compiler
CXX := g++

# Executable name
EXEC := main

# Source files
SOURCES := main.cpp player.cpp level.cpp

# Object files directory
OBJDIR := obj

# Object filesf
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(addprefix $(OBJDIR)/,$(OBJECTS))

# Compiler flags
CXXFLAGS := -std=c++17

# Include directories
INCLUDES := -I./ -I/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/externals/SFML/include


# Linker flags
LDFLAGS := -L/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/externals/externals/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

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
