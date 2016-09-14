#pragma once
#include "binary_heap.h"
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <string>
#include "../constants/constants.h"
#include "../args/action.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
    /**
     * namespace that keeps track of data for the application. Currently
     * that is only the maze and associated classes / structs but this
     * may grow.
     **/
    namespace data
    {
        /**
         * enumeration that defines the current orientation for the 
         * algorithm. At each recursive call, we swap orientation
         **/
        enum orientation
        {
            /// the orientation is currently horizontal
            HORIZONTAL, 
            /// the orientation is currently vertical
            VERTICAL
        };

        /**
         * ! (not) operator implemented for an orientation enumeration
         * so that it reverses direction (say HORIZONTAL becomes 
         * VERTICAL, etc)
         **/
        orientation operator !(const orientation);
        /**
         * two orientations - HORIZONTAL and VERTICAL
         **/
        const int NUM_ORIENTATIONS = 2;

        /**
         * enumeration that represents a direction from a cell in terms
         * of the traditional cardinal directions: north, south, etc.
         **/
        enum class direction
        {
            /**
             * represents a cell above the current cell
             **/
            NORTH, 
            /**
             * represents a cell below the current cell
             **/
            SOUTH, 
            /**
             * represents a cell to the left of the current cell
             **/
            EAST, 
            /**
             * represents a cell to the right of the current cell
             **/
            WEST, 
            /**
             * represents an invalid direction
             **/
            INVALID
        };

        /**
         * operator function that turns its direction into its opposite - 
         * north becomes south, etc.
         **/
        const direction operator!(const direction);

        /**
         * the number of valid directions from a cell
         **/
        const int num_dirs = 4;

        /**
         * calculates the direction of a specified x,y-x,y coordinates.
         * Note that the direction will ge invalid if they are in a
         * diagonal direction from each other or not adjacent.
         **/
        direction get_dir(const int in_x, 
                const int in_y, const int out_x, const int out_y);

        /**
         * struct that represents an edge in the maze. We have the in 
         * coordinates which are the coordinates of the current cell and 
         * out coordinates which are the coordinates of the destination
         * cell. We also have a boolean for whether this edge has been
         * visited so we don't process an edge twice.
         **/
        struct edge
        {
            ///the cell's x coordinate
            int in_x, 
                ///the cell's y coordinate
                in_y, 
                ///the edge's destination x coordinate
                out_x, 
                ///the edge's destination y coordinate
                out_y;
            ///whether this edge has been visited in the current algorithm
            bool visited, solution_path;

            /**
             * I needed to change the default initialisation of an edge
             * as an empty edge should have all coordinates intialized to
             * -1 in my implementation.
             **/
            edge(void) 
                : in_x(constants::ERROR), in_y(constants::ERROR),
                out_x(constants::ERROR), out_y(constants::ERROR), 
                visited(false),  solution_path(false)
            {
            }        

            /**
             * need to provide a parameterised constructor if I provide 
             * a default or it becomes hidden
             **/
            edge(int x1, int y1, int x2, int y2) 
                : in_x(x1), in_y(y1), out_x(x2), 
                out_y(y2), solution_path(false)
            {
            }
            

        };

        // Compare 2 edges for equality
        bool operator == (const edge& a, const edge& b);

		// Compare 2 edges. @returns true if lhs is 'lesser'
        bool operator < (const edge& a, const edge& b);
		// Compare 2 edges. @returns true if lhs is 'greater'
        bool operator > (const edge& a, const edge& b);
		
		std::ostream & operator<<(std::ostream&, const edge&);
        /**
         * provide the ! operator which will swap the in and out 
         * coordinates
         **/
        edge operator!(const edge& );

        /**
         * struct that represents a cell in the maze. It has an x,y 
         * coordinate, and a vector of edges from this cell to other
         * cells
         **/
        struct cell
        {
            ///the x coordinate of the current cell
            int x
                ///the cell's y coordinate
                , y;
            ///vector of edges that link to adjacent cells
            std::vector <edge> adjacents;
            int parent_x, parent_y, dist = std::numeric_limits<int>::max(),
				this_cost = 0;
			bool in_maze, in_walk, loop;
			cell * parent;
			//cell * child = nullptr;
            /**
             * default constructor - initializes the adjacents vector to 
             * a vector of size 4 and this cell's coordinates to an 
             * empty location
             **/
            cell(void) : x(constants::ERROR), y(constants::ERROR), 
                adjacents(num_dirs), in_maze(false), in_walk(false),
				loop(false), parent(nullptr)
            {
            }

            /**
             * constructor which takes the coordinates of the cells and
             * initializes the adjacents vector to a size of 4.
             **/
            cell(int _x, int _y) : x(_x), y(_y), 
            adjacents(num_dirs), in_maze(false), in_walk(false),
			loop(false), parent(nullptr)
            {
            }
        };
		// Compare 2 cells. @returns true if lhs is 'lesser'
        bool operator < (const cell& a, const cell& b);

        /**
         * the maze class itself - represents a maze which has been 
         * generated or loaded
         **/
        class maze
        {
            ///the width of the maze
            int _width, 
                ///the height of the maze
                _height;
            ///the vector of vector of cells that represents the maze itself
            std::vector < std::vector < cell > > _cells;
            ///has this maze been initialized?
            bool _initialized;

            ///the maximum resolution for outputting as svg - required
            ///by my algorithm. Note that under c++11 onwards if I 
            ///initalize a static inside the class it must be a constexpr
            ///, that is, it must be resolvable at compile time.
            constexpr static const double MAXRES=500;


	    friend std::ostream & operator<<(std::ostream&, const maze&);
	    friend std::ostream & operator<<(std::ostream&, const cell&);
            public:

            /**
             * default constructor - constructs a maze of 0 width and 
             * height and puts the maze in an uninitialized state.
             **/
            maze(void) 
                : _width(0), _height(0), _cells(0), _initialized(false)
            {
            }

            /**
             * parameterized constructor - constructs a maze of the 
             * specified width and height and puts the maze in an 
             * uninitialized state.
             * @param width the width of the maze to create
             * @param height the height of the maze to create
             **/
            maze ( int width, int height ) 
                : _width ( width ) , _height ( height ) , 
                //initialize the _cells vector to be the correct
                //width and height
                _cells ( height , std::vector < cell > ( width ) ),
                _initialized(false)
            {
            }

            /**
             * returns whether this maze has been initialized or not.
             * It has not been initialized until we build the maze - 
             * we don't want to write out a non-existent maze.
             **/
            bool initialized(void)
            {
                return _initialized;
            }

            /**
             * @return a reference to the cells vector to manipulate
             * that locally. If you have a handle to a maze you should
             * have access to the cells. I thought about making cells 
             * public but by implementing this in the class declaration, 
             * there is no time overhead to call this function and 
             * there is no space overhead for it being an inline function
             * as there is only a return statement anyway.
             **/
            std::vector<std::vector<cell>> & get_cells(void) 
            {
                return _cells;
            }

            /**
             * getter for the height of the maze
             * @return the maze height
             **/
            int height() const
            {
                return _height;
            }

            /**
             * setter for the maze height. It sets the height then 
             * resizes the _cells vector to match that height and 
             * each row vector to match the current width
             * @param h the new height for this maze.
             **/
            void height(const int h)
            {
                _height = h;
                //change the height of the adjacency matrix
                _cells.resize(h);
                //change the width of the adjacency matrix
                for (auto & element : _cells)
                    element.resize(_width);
            }

            /**
             * @return the width of this maze
             **/
            int width() const
            {
                return _width;
            }

            /**
             * change the width of this maze.
             * changing the width of this maze means resizing each row
             * of the adjacency matrix
             **/
            void width( const int w )
            {
                _width = w;
                //resize each row
                for(auto & element : _cells)
                {
                    element.resize(w);
                }
            }

            /**
             * sets the initialized variable so that we don't try to 
             * write out a maze that has not been generated.
             **/
            void init(void);

            /**
             * saves this maze in binary format.
             **/
            bool save_binary(const std::string&);

            /**
             * loads a maze in binary format from a file and initializes
             * the instance data of this maze with that data.
             **/
            bool load_binary(const std::string&);

            /**
             * saves this maze as an svg file.
             **/
            bool save_svg(const std::string&);

            /**
             * writes the svg prolog to a file.
             **/
            void save_svg_prologue(std::ofstream&,double);

            /**
             * writes the closing tag for an svg file to the file 
             * specified.
             **/
            void save_svg_epilogue(std::ofstream&);

            /**
             * saves an edge from this maze to an svg file.
             **/
            void save_svg_edge(std::ofstream&, const edge&, double);

			/**
			 * Saves the solution path in red
			 **/ 
			void solution_edge(std::ofstream &, const edge&, double);
            /**
             * writes the background rectangle for this maze to an 
             * svg file
             **/
            void save_svg_background(std::ofstream&, double);

            /**
             * sets every edge in this maze to be unvisited. 
             * This is necessary for some algorithms such as the 
             * saving of the svg file as we don't want to write 
             * edges to the file twice
             **/
            void set_unvisited(void);

            /**
             * gets the number of edges in this maze
             **/
            int edge_count(void);

            /**
             * sets a particular edge to be visited. We pass in the 
             * e_index within a cell so we can set the opposing edge
             * as well.
             **/
            void set_visited( edge& e, int e_index);

            /**
             * is this a valid edge? a valid edge is one where all 
             * coordinates a valid reference within the _cells
             * vector.
             **/
            bool valid_edge(const edge&) const;

	    maze(const maze & m)
	    {
		std::cout << "copying the maze" << std::endl;
		
	    }

            bool valid_dim(const int);

	    void clear(void);
	    
        };
    }
}


