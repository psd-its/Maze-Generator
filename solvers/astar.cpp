#include "astar.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

void mazer2016sp1oua::solvers::astar::solve ()
{
	//get the cells in the maze 
	auto& cells = maze_ref.get_cells();
	
	// Ensure that there is not an existing solution 
	for (int y= 0; y < maze_ref.height(); ++y)
	{
		for (int x = 0; x < maze_ref.width(); ++x)
		{
			for (auto & e : cells[y][x].adjacents)
			{   // reset the values that dictate a solution path 
				cells[y][x].dist = INT_MAX;
				cells[y][x].this_cost = 0;
				if(maze_ref.valid_edge (e))
				{
					e.solution_path = false;
				}
			}
		}
	}
	std::cout << "Solving maze...." << std::endl;
	bool solved = false;
	auto& start = cells[constants::START][constants::START];
	// Mark the starting cells parent
	start.parent_x = constants::ERROR;
	// get starting cells neighbours
	for (auto& i : start.adjacents)
	{
		if (maze_ref.valid_edge (i))
		{
			auto& pos_cell = cells[i.out_y][i.out_x];
			pos_cell.this_cost += cost;
			pos_cell.dist = calc_dist(i.out_x, i.out_y) + pos_cell.this_cost;
			pos_cell.parent_x = i.in_x;
			pos_cell.parent_y = i.in_y;
			open.push(i);
		}
	}
	while(!open.empty())
	{   // Get the value with the lowest F value (dist)
		auto current = open.front();
		auto key = std::make_tuple(current.in_x, current.in_y);		
		open.pop();
		// Add it to the closed list
		closed.insert({key, current});
		// check if we are the end of the maze
		if (current.out_x == maze_ref.width()-1 &&
		    current.out_y == maze_ref.height () -1)
		{
			solved = true;
			// Parent and current x/y coords
			int p_x, p_y, c_x, c_y;
			c_x = current.out_x;
			c_y = current.out_y;
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
			}
			//std::cout << "Your maze has been solved!" << std::endl;
			break;
		}
		// get the adjacents of the current cell
		auto& cur_cell = cells[current.out_y][current.out_x];
		for (auto& i : cur_cell.adjacents)
		{   //only look at valid edges
			if (maze_ref.valid_edge (i))
			{   // Check that this cell is not in the closed list
				auto tup = std::make_tuple(i.out_x, i.out_y);
				if(closed.find(tup) == closed.end())
				{
					auto& pos_cell = cells[i.out_y][i.out_x];
					// Cell has not been inspected yet
					if (pos_cell.dist == INT_MAX)
					{
						pos_cell.this_cost = cur_cell.this_cost + cost;
						pos_cell.dist = calc_dist(i.out_x, i.out_y) + 
							pos_cell.this_cost;
					}
					else
					{   // There is already a faster was to reach this cell
						if (pos_cell.this_cost < cur_cell.this_cost + cost)
							continue;
						else
						{   //Set the cost so far and calculate the distance
							pos_cell.this_cost = cur_cell.this_cost + cost;
							pos_cell.dist = calc_dist(i.out_x, i.out_y) + 
								pos_cell.this_cost;
						}
					}
					// set the parent and add it to the set
					pos_cell.parent_x = i.in_x;
					pos_cell.parent_y = i.in_y;
					open.push(i);
				}
			}
		}
	}
	if (!solved)
	{   // Print error if we cant solve the maze
		std::cout << "Your maze is unsolveable" << std::endl;
		return;
	}
	/*	// Get the end of the maze
	 auto& cur = cells[maze_ref.height()-1][maze_ref.width()-1];
	 while (cur.parent_x != constants::ERROR)
	 {   // Step through the parent cells marking the solution path
		 for (auto & i : cur.adjacents)
		 {
			 if (i.out_x == cur.parent_x && i.out_y == cur.parent_y)
			 {
				 i.solution_path = true;
}
}
cur = cells[cur.parent_y][cur.parent_x];

}*/
	std::cout << "Maze solve in: ";
}




