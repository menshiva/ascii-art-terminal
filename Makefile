# Project: ASCII art
# Author:  Ivan Menshikov

THREADS_NUM = $(shell grep -c 'processor' /proc/cpuinfo)
MAKEFLAGS += -j$(THREADS_NUM)

PROGRAM = ASCII_art
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

# all: compile run clean

compile: $(PROGRAM)

run:
	./$(PROGRAM)

# doc: $(SRC) $(HDR) Doxyfile
# 	doxygen

clean:
	rm -f $(PROGRAM)
	rm -rf $(OBJDIR)
	rm -rf doc

$(PROGRAM): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
