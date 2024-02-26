# Doxygen-Kommentare
# @file Makefile
# @brief Makefile für das SDL Platformer-Projekt.
#
# Definiert Regeln zum Kompilieren des SDL Platformer-Spiels und zum Aufräumen generierter Dateien.

# Name des ausführbaren Ziels
TARGET=sdl_platformer

# Compiler und Compiler-Flags
CC=cc
CFLAGS=

# SDL-Bibliothekspfade und -Flags
SDL_FLAGS=-I/usr/include/SDL2 -lSDL2 -lSDL2_ttf

# WiringPi-Bibliothek
WIRINGPI_LIB=-lwiringPi

# Mathematikbibliothek
MATH_LIB=-lm

# Dateierweiterungen für die Quell- und Header-Dateien
SRC_EXT=.c
HDR_EXT=.h

# Automatische Erkennung aller Quell- und Header-Dateien im aktuellen Verzeichnis
SOURCES=$(wildcard *$(SRC_EXT))
HEADERS=$(wildcard *$(HDR_EXT))

# Ableitung der Objektdateien aus den Quelldateien
OBJECTS=$(SOURCES:$(SRC_EXT)=.o)

# Hauptziel: Kompiliert das Projekt
all: $(TARGET)

# Regeln zum Erstellen des ausführbaren Ziels
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(SDL_FLAGS) $(WIRINGPI_LIB) $(MATH_LIB) -o $@

# Regel zur Erstellung von Objektdateien
%.o: %$(SRC_EXT) %$(HDR_EXT)
	$(CC) $(CFLAGS) -c $< -o $@

# Regel zum Bereinigen des Projekts, entfernt .o Dateien und das ausführbare Ziel
clean:
	rm -f $(TARGET) $(OBJECTS)
