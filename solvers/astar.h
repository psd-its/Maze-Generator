#pragma once
#include "../data/maze.h"
#include <cmath>
#include <tuple>
#include <map>
#include "../constants/constants.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
	namespace solvers
	{
		class astar
		{
			heap<data::edge> open;
			std::map<std::tuple<int,int>, data::edge> closed;
			data::maze& maze_ref;
			const constants::huristic h_type;
			const int cost = 1;
			
			public:
				astar(mazer2016sp1oua::data::maze& m, constants::huristic h) :
				maze_ref(m), h_type(h) 
				{			
				}
				
				virtual void solve(void);

				//get the distance using appropriate huristic
				int calc_dist(int x, int y)
				{
					if (h_type == constants::huristic::EUCLIDEAN)
					{
						return sqrt((pow(maze_ref.height() - y , 2))+
	                    (pow(maze_ref.width() - x, 2)));
					}
					
					return (maze_ref.height() - y) + (maze_ref.width() - x);
					
				}
				/*// calculate the euclidean distance using pythagoras
				constexpr int calc_e(int x, int y)
				{
					return sqrt((pow(maze_ref.height() - y , 2))+
	                    (pow(maze_ref.width() - x, 2)));
				}

				// calculate the manhatten distance 
				constexpr int calc_m(int x, int y)
				{
					return (maze_ref.height() - y) + (maze_ref.width() - x);
				}*/
				
		};
		

		
	}
	
}