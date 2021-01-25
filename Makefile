# Project: ASCII art
# Author:  Ivan Menshikov

PROGRAM = menshiva
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wpedantic -Wextra -O3
LIBFLAGS = -L/usr/lib/x86_x64-linux-gnu -lpanel -lmenu -lncurses -pthread -lstdc++fs -ljpeg

SRCDIR = src
OBJDIR = build

SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
HDR = $(shell find $(SRCDIR)/ -type f -name '*.hpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: compile run

val: compile runVal

compile: $(PROGRAM)

run:
	./$(PROGRAM)

doc: $(SRC) $(HDR) Doxyfile
	doxygen

runVal:
	/usr/bin/valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(PROGRAM)

clean:
	rm -f $(PROGRAM)
	rm -rf $(OBJDIR)
	rm -rf doc

$(PROGRAM): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
