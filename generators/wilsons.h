
#include "../data/maze.h"
#include <tuple>
#include <string>
#include <map>
#include "../data/willmap.h"
#include <exception>
#include <iostream>
#include <memory>
#include <algorithm>

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
    namespace generators
    {
        class wilsons
        {
            mazer2016sp1oua::data::maze & mmaze;
			std::vector<std::vector<data::cell>> & cells = mmaze.get_cells ();
            //index of each cell as an array
            std::vector<std::tuple<int,int>> _starts;
            //our random number generator
            std::mt19937 rnd_gen;
			std::multimap<std::tuple<int,int>, data::edge> inmaze;
            willmap<std::tuple<int,int>, data::edge> inwalk;
			
            public:
                //constructor takes a maze reference as parameter
                wilsons(mazer2016sp1oua::data::maze& maze, int width, 
                        int height, int seed) : mmaze(maze), rnd_gen(seed)
                {
                    mmaze.height(height);
                    mmaze.width(width);
                        //clear all connections
                    mmaze.clear();
                        std::cout << "seed for this generator is: " <<
                            seed << std::endl;
                    init_starts();
                }

                // Generate a maze using wilsons algorithm
                void generate(void);     
                // create a list of each cell in the maze
                void init_starts(void)
                {
					auto cells = mmaze.get_cells ();
                    for (int y = 0; y < mmaze.height(); ++y)
                    {
                        for (int x = 0; x < mmaze.width(); ++x)
                        {
                            std::tuple<int, int> start = 
                                std::make_tuple(y,x);
                            _starts.push_back(start);
							cells[y][x] = data::cell(x,y);
                        }
                    }
                }
				
                bool go_dir(int&, int&, data::direction);
                int expected()
                {
                    return mmaze.height() * mmaze.width() -1;
                }
                bool loop_check(const int&, const int&);
        };

        // exception used to signal that walk has looped
        class loop_error : public std::exception
        {
            public:
                loop_error(){}
        };

		class maze_found : public std::exception
        {
			std::tuple<int,int> key;
            public:
                maze_found(std::tuple<int,int> t): key(t){}

				std::tuple<int,int> get_key()
				{
					return key;
				}
        };

        enum class will_dir
        {
            LEFT, RIGHT, FORWARD
        };
		std::ostream& operator << (std::ostream& out, 
		                           const std::tuple<int,int>& tup);
	
		

        
    }
}