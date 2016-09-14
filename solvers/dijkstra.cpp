#include "dijkstra.h"

/**********************
 *       Mazer        *
 * By Tristan Mcswain *
 *      s3528615      *
 **********************/

void mazer2016sp1oua::solvers::dijkstras::solve (void)
{
	using namespace mazer2016sp1oua::data;
	maze_ref.set_unvisited ();
	auto & cells = maze_ref.get_cells();
	std::cout << "Solving...." << std::endl;
	bool solved = false;
	
	// Set the parent of the starting node to -1 signaling error
	cells[constants::START][constants::START].parent_x = constants::ERROR;
	cells[constants::START][constants::START].parent_y = constants::ERROR;
	cells[constants::START][constants::START].dist = 0;

	// Get the first edge in the maze
	for (auto & e : cells[constants::START][constants::START].adjacents)
	{
		if (!e.visited && maze_ref.valid_edge(e))
		{   
			cells[e.out_y][e.out_x].dist = cells[e.in_y][e.in_x].dist + 1;
			path.push(e);   
		}       
	}

	// Start the search
	while (!path.empty() && !solved)
	{
		// Grab the edge at the front of the queue
		edge current = path.front();
		path.pop();
		//mark the current edge visited
		current.visited = true;
		// Grab the reverse edge and mark it visited, the function set_visited
		// is supposed to do this but it doesn't appear to be working
		for( auto &rev : cells[current.out_y][current.out_x].adjacents)
		{
			if (rev == !current && maze_ref.valid_edge (rev) && !rev.visited)
			{
				// Set parent cell
				cells[rev.in_y][rev.in_x].parent_x = rev.out_x;
				cells[rev.in_y][rev.in_x].parent_y = rev.out_y;

				rev.visited = true;    
			}
		}
		// Print is for debugging
#ifdef DEBUG
		std::cout << current << std::endl;
#endif


		// Grab the edges adjacent to the current edge and add them to
		// the queue

		for (auto i : cells[current.out_y][current.out_x].adjacents)
		{
			if (!i.visited && maze_ref.valid_edge(i))
			{
				cells[i.out_y][i.out_x].dist = cells[i.in_y][i.in_x].dist + 1;
				path.push(i);
			}
		}     

	}
	// Check if we are at our destination
	edge last;
	//minimum distance calculated with pythagoras
	int min_dist = sqrt((pow(maze_ref.height(),2))+
	                    (pow(maze_ref.width(),2)));
	std::cout << min_dist << std::endl;
	for (auto & e : cells[maze_ref.height()-1][maze_ref.width()-1].adjacents)
	{
		if (!maze_ref.valid_edge (last)){last = e;}
		
		if(maze_ref.valid_edge(e) &&
		   cells[e.out_y][e.out_x].dist < cells[last.out_y][last.out_x].dist
		   && cells[e.out_y][e.out_x].dist > min_dist)
		{
			last = e;
		}
		
	}
	last.solution_path = true;	
	// Parent and current x/y coords
	int p_x, p_y, c_x, c_y;
	c_x = last.out_x;
	c_y = last.out_y;
	p_x = cells[c_y][c_x].parent_x;
	p_y = cells[c_y][c_x].parent_y;
	// while not back at the start of maze
	while (p_x != constants::ERROR)
	{
		for (auto& e : cells[c_y][c_x].adjacents)
		{
			if (e.in_x == c_x && e.in_y == c_y &&
			    e.out_x == p_x && e.out_y == p_y)
			{
				e.solution_path = true;
			}
		}
		// step backwards through the maze
		c_x = p_x;
		c_y = p_y;
		p_x = cells[c_y][c_x].parent_x;
		p_y = cells[c_y][c_x].parent_y;
		if (p_x == constants::ERROR)
		{
			solved = true;
		}

	}
	// If the maze has not been solved
	if (!solved)
	{
		std::cout << "Your maze is not solveable!" << std::endl;
		return;
	}
	std::cout << "Your maze has been solved in: " << std::endl;

}
