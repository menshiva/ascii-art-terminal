# Project: ASCII art
# Author:  Ivan Menshikov

PROGRAM = ascii_art
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Wextra -O3
LIBFLAGS = -L/usr/lib/x86_x64-linux-gnu -lpanel -lmenu -lncurses -pthread -lstdc++fs -ljpeg

SRCDIR = src
OBJDIR = build

SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
HDR = $(shell find $(SRCDIR)/ -type f -name '*.hpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

install:
	sudo apt install libncurses-dev libjpeg-dev

compile: $(PROGRAM)

run:
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM)
	rm -rf $(OBJDIR)
	rm -rf doc

$(PROGRAM): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
