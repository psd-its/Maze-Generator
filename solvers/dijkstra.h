#include "../data/maze.h"
#pragma once
#include <cmath>
#include "../constants/constants.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
	namespace solvers
	{
		
		
		class dijkstras 
		{
			heap<data::edge> path;
			data::maze& maze_ref;
			public:
				dijkstras(mazer2016sp1oua::data::maze& m) : maze_ref(m) {}

				virtual void solve(void);
		};
	}
}