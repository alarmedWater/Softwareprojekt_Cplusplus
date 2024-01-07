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



# SFML include and library paths
SFML_DIR = /home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/externals/SFML
SFML_INCLUDE = -I$(SFML_DIR)/include
SFML_LIBS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

# Your compiler flags (add SFML_INCLUDE here)
CXXFLAGS = -std=c++17 $(SFML_INCLUDE)

# Your linker flags (add SFML_LIBS here)
LDFLAGS = $(SFML_LIBS)


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
