############################################################################
# mazer2016 - an implementation of the assignment 1 specification for
# CPT323 - Object Oriented Programming Using C++.
#
# Developed by Paul Miller. This solution can be used as a starting point for
# Assignment 2.
#
# /*******************
# * Tristan Mcswain *
# *     s3528615    *
# *******************/ 
############################################################################

#object files created as part of compilation
OBJECTS=data/maze.o generators/binary_gen.o main.o args/action.o \
	args/arg_processor.o solvers/bfs_solver.o generators/wilsons.o \
	generators/sidewinder.o solvers/dijkstra.o solvers/astar.o
#header files included in various files.
HEADERS=data/maze.h generators/binary_gen.h args/action.h \
	args/arg_processor.h constants/constants.h solvers/bfs_solver.h \
    data/binary_heap.h generators/wilsons.h generators/sidewinder.h \
	solvers/dijkstra.h solvers/astar.h data/willmap.h
CXXFLAGS=-Wall -pedantic -Werror -std=c++14
LFLAGS=
#how do we create the binary for execution
all: $(OBJECTS) TAGS
	g++ $(LFLAGS) $(OBJECTS) -o mazer

#how do we make each individual object file? 
%.o: %.cpp $(HEADERS)
	g++ $(CXXFLAGS) -c $< -o $@

#generate tags for use with emacs - allows easy search for function names
TAGS:
	ctags -e -R .

#how do we do cleanup so that we only have the source files?
.PHONY:clean
clean:
	rm -f $(OBJECTS) mazer TAGS

#run program in debug mode
debug:CXXFLAGS+=-DDEBUG -g
debug:clean all

#clean all files needed for compilation as well as svg files
.PHONY:svgclean
svgclean : clean
	rm -f *.svg
