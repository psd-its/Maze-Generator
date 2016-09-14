
#pragma once
#include "../constants/constants.h"
#include <memory>
#include "../data/maze.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
    namespace solvers
    {
		
		class Solve_bfs
		{
			protected:
				std::vector<mazer2016sp1oua::data::edge> path;
				mazer2016sp1oua::data::maze& maze_ref;
			public:
				// Constructor
				Solve_bfs(mazer2016sp1oua::data::maze& maze) : maze_ref(maze){}
				~Solve_bfs (){}
				// Solve maze prototype
				virtual void solve();
		};
		
    }

}

// This is no longer used was initially using it instead of static cast 
// to get direction
template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}
