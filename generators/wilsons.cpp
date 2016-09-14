#include "wilsons.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

void mazer2016sp1oua::generators::wilsons::generate(void)
{
	std::cout << "Generating..." << std::endl;
	std::uniform_int_distribution<int> rnd_dir(0, 2);
	auto & cells = mmaze.get_cells ();
	auto cur_dir = data::direction::SOUTH;
	//int edges = 0, error_count = 0;
	// Make a copy of the start coords
	int cur_x , cur_y, prev_x, prev_y;
	bool wander, start_found;
	// pick an initial starting point and remove it from the
	// vector of possible starts
	std::uniform_int_distribution<int> rand_start(0, _starts.size ()-1);
	int index = rand_start(rnd_gen);
	auto start_p = _starts[index];
	std::cout << "starting point " << start_p << std::endl;
	cur_x = std::get<1>(start_p);
	cur_y = std::get<0>(start_p);
	cells[cur_y][cur_x].in_maze = true;
	/*in_maze.push_back(std::make_tuple(cur_y,cur_x));
	++ edges;*/
	_starts.erase(_starts.begin()+ index);
	while(!_starts.empty())
	{  
		wander = true;
		start_found = false;
		// randomly select a walk startpoint out of the remaining coords
		std::uniform_int_distribution<int> rand_start(0, _starts.size()-1);
		while (!start_found)
		{
			std::uniform_int_distribution<int> rand_start(0, _starts.size()-1);
			index = rand_start(rnd_gen);
			auto start = _starts[index];
			cur_x = std::get<1>(start);
			cur_y = std::get<0>(start);
			if (cells[cur_y][cur_x].in_maze)
			{
				_starts.erase(_starts.begin()+ index);
				if (_starts.empty())
					break;
			}
			else
			{
				start_found = true;
#ifdef DEBUG
				std::cout << "starting walk from " << start << "_____________"
					<< "______________________________________" << std::endl;
#endif
			}
		}
		// Remove the starting coords from the array so it can't be selected
		// again. Maintaining this vector of unvisited nodes cuts down on 
		// random calls to find a start point dramatically when the maze 
		// starts to fill up.
	
		while (wander)
		{
			// Get a random direction
			will_dir dir = static_cast<will_dir>(rnd_dir(rnd_gen));
			// keep track of the previous coords used incase of a loop
			prev_x = cur_x;
			prev_y = cur_y;
			try
			{
				switch(dir)
				{
					// Randomly selected to turn left
					case will_dir::LEFT:
					{
					// currently going north
					if (cur_dir == data::direction::NORTH)
					{
						// Try to turn left
						if (go_dir(cur_x, cur_y, data::direction::WEST))
						{
							// cells[cur_y][cur_x].in_walk = true;
							cur_dir = data::direction::WEST;
						}
						break;
					}
					// currently going south
					else if (cur_dir == data::direction::SOUTH)
					{
						//Try to turn left
						if (go_dir(cur_x, cur_y, data::direction::EAST))
						{
							// cells[cur_y][cur_x].in_walk = true;
							cur_dir = data::direction::EAST;    
						}
						break;
					}
					// Currently heading east
					else if (cur_dir == data::direction::EAST)
					{
						// Try to turn left
						if (go_dir(cur_x, cur_y, data::direction::NORTH))
						{
							// cells[cur_y][cur_x].in_walk = true;
							cur_dir = data::direction::NORTH;    
						}
						break;
					}
					//Currently heading west
					else
					{
						// Try to turn left
						if (go_dir(cur_x, cur_y, data::direction::SOUTH))
						{
							// cells[cur_y][cur_x].in_walk = true;
							cur_dir = data::direction::SOUTH; 
						}
						break;
					}
					// If we get tor here something has gone wrong
					break;
				}
						// Randomly selected to go right
					case will_dir::RIGHT:
					{    
						// Currently going north
						if (cur_dir == data::direction::NORTH)
						{
							//Try to turn right
							if (go_dir(cur_x, cur_y, data::direction::EAST))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::EAST;    
							}
							break;
						}
						// Currently going south
						else if (cur_dir == data::direction::SOUTH)
						{
							// Try to turn right
							if (go_dir(cur_x, cur_y, data::direction::WEST))
							{
								// cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::WEST;    
							}
							break;
						}
						// Currently going east
						else if (cur_dir == data::direction::EAST)
						{
							// Try to turn right
							if (go_dir(cur_x, cur_y, data::direction::SOUTH))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::SOUTH;    
							}
							break;
						}
						// Currently going west
						else
						{
							// try to turn right
							if (go_dir(cur_x, cur_y, data::direction::NORTH))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::NORTH;    
							}
							break;
						}
						// If we get tor here something has gone wrong
						break;

					}
					case will_dir::FORWARD:
					{
						// Currently going north
						if (cur_dir == data::direction::NORTH)
						{
							//Try to continue on current path
							if (go_dir(cur_x, cur_y, data::direction::NORTH))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::NORTH;    
							}
							break;
						}
						// Currently going south
						else if (cur_dir == data::direction::SOUTH)
						{
							//Try to continue on current path
							if (go_dir(cur_x, cur_y, data::direction::SOUTH))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::SOUTH;    
							}
							break;
						}
						// Currently going east
						else if (cur_dir == data::direction::EAST)
						{
							//Try to continue on current path
							if (go_dir(cur_x, cur_y, data::direction::EAST))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::EAST;    
							}
							break;
						}
						// Currently going west
						else
						{
							//Try to continue on current path
							if (go_dir(cur_x, cur_y, data::direction::WEST))
							{
								//cells[cur_y][cur_x].in_walk = true;
								cur_dir = data::direction::WEST;    
							}
							break;
						}
						// If we get tor here something has gone wrong
						break;
					}
				}

				if (cells[cur_y][cur_x].in_maze)
				{
					data::cell* maze_start = &cells[cur_y][cur_x];
					data::cell* cur = maze_start -> parent;
					data::cell* temp;
					while(cur != nullptr)
					{
						cur -> in_walk = false;
						cur -> in_maze = true;
						temp = cur;

						/*if(cur -> parent == nullptr)
						break;*/
						cur = cur -> parent;
						temp -> parent = nullptr;
					}
					wander = false;

				}
			}
			catch(loop_error& le)
			{
				data::cell * cur, * temp;
				
				cur = &cells[prev_y][prev_x];
				
				do
				{
					if (cur != nullptr)
					{
						for(auto &i : cur -> adjacents)
						{
							i = data::edge (constants::ERROR,constants::ERROR,
							                constants::ERROR,constants::ERROR);
						}
					}
					else
						break;
					cur -> in_walk = false;
					temp = cur;
					if(cur -> parent == nullptr)
						break;
					cur = cur -> parent;
					temp -> parent = nullptr;
				}while(!cur -> loop);
				/*delete cur;
				delete temp;
*/
			}
			
		}
	}
	mmaze.init ();
	std::cout << "Completed in: ";
}



bool mazer2016sp1oua::generators::wilsons::go_dir(int& cur_x, int& cur_y, 
                                                  mazer2016sp1oua::data::direction dir)
{
	//auto & cells = mmaze.get_cells ();
	auto& cur_cell = cells[cur_y][cur_x];
	// Edges in oposing directions
	data::edge out_edge, in_edge;
	switch(dir)
	{
		case data::direction::WEST:
		{
		if (cur_x == 0)
			return false;
		//create the edges that go both out from here and
		//in from here
		out_edge.in_x = in_edge.out_x = cur_x;
		out_edge.in_y = in_edge.out_y = cur_y;
		out_edge.out_x = in_edge.in_x = cur_x -1;
		out_edge.out_y = in_edge.in_y = cur_y;

		if(loop_check (cur_y, cur_x))
		{
			cur_cell.loop = true;
			throw loop_error();
		}

		cur_x = out_edge.out_x;
		cur_y = out_edge.out_y;

		cur_cell.adjacents[int(mazer2016sp1oua::data::direction::WEST)] = 
			out_edge;
		cur_cell.in_walk = true;
		auto & alt_cell = cells[cur_y][cur_x];
		alt_cell.parent = &cur_cell;
		alt_cell.adjacents[int(mazer2016sp1oua::data::direction::EAST)] =
			in_edge;

		return true;
	}
		case data::direction::EAST:
		{
			if (cur_x == mmaze.width()-1)
				return false;
			//create the edges that go both out from here and
			//in from here
			out_edge.in_x = in_edge.out_x = cur_x;
			out_edge.in_y = in_edge.out_y = cur_y;
			out_edge.out_x = in_edge.in_x = cur_x + 1;
			out_edge.out_y = in_edge.in_y = cur_y;

			if(loop_check (cur_y, cur_x))
			{
				cur_cell.loop = true;
				throw loop_error();
			}
			cur_x = out_edge.out_x;
			cur_y = out_edge.out_y;
			cur_cell.adjacents[int(mazer2016sp1oua::data::direction::EAST)] = 
				out_edge;
			cur_cell.in_walk = true;
			auto & alt_cell = cells[cur_y][cur_x];
			alt_cell.parent = &cur_cell;
			alt_cell.adjacents[int(mazer2016sp1oua::data::direction::WEST)] =
				in_edge;
			return true;

		}
		case mazer2016sp1oua::data::direction::NORTH:
		{
			if (cur_y == 0)
				return false;
			out_edge.in_x = in_edge.out_x = cur_x;
			out_edge.in_y = in_edge.out_y = cur_y;
			out_edge.out_x = in_edge.in_x = cur_x;
			out_edge.out_y = in_edge.in_y = cur_y -1;

			if(loop_check (cur_y,cur_x))
			{
				cur_cell.loop = true;
				throw loop_error();
			}
			cur_x = out_edge.out_x;
			cur_y = out_edge.out_y;
			cur_cell.adjacents[int(mazer2016sp1oua::data::direction::NORTH)] = 
				out_edge;
			cur_cell.in_walk = true;

			auto & alt_cell = cells[cur_y][cur_x];
			alt_cell.parent = &cur_cell;
			alt_cell.adjacents[int(mazer2016sp1oua::data::direction::SOUTH)] =
				in_edge;
			return true;
		}
		case mazer2016sp1oua::data::direction::SOUTH:
		{
			if (cur_y == mmaze.height()-1)
				return false;
			//create the edges that go both out from here and
			//in from here
			out_edge.in_x = in_edge.out_x = cur_x;
			out_edge.in_y = in_edge.out_y = cur_y;
			out_edge.out_x = in_edge.in_x = cur_x;
			out_edge.out_y = in_edge.in_y = cur_y + 1;

			if(loop_check (cur_y,cur_x))
			{
				cur_cell.loop = true;
				throw loop_error();
			}
			cur_cell.in_walk = true;
			cur_x = out_edge.out_x;
			cur_y = out_edge.out_y;
			cur_cell.adjacents[int(mazer2016sp1oua::data::direction::SOUTH)] = 
				out_edge;
			auto & alt_cell = cells[cur_y][cur_x];
			alt_cell.parent = &cur_cell;
			alt_cell.adjacents[int(mazer2016sp1oua::data::direction::NORTH)] =
				in_edge;
			return true;
		}
		case mazer2016sp1oua::data::direction::INVALID:
		{
			return false;
		}
	}
	// should never reach this
	return false;
}

inline bool mazer2016sp1oua::generators::wilsons::loop_check(const int& y,
                                                             const int& x)
{
	return cells[y][x].in_walk;
}

std::ostream& mazer2016sp1oua::generators::operator << (std::ostream& out, 
                                              const std::tuple<int,int>& tup)
{
	out << "(x:" << std::get<1>(tup) << ") : (y:" << std::get<0>(tup) <<") ";
	return out;
}


