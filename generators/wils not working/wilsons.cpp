#include "wilsons.h"

void mazer2016sp1oua::generators::wilsons::generate(void)
{
	std::cout << "Generating..." << std::endl;
	std::uniform_int_distribution<int> rnd_dir(0, 3);
	
	// Make a copy of the start coords
	int cur_x , cur_y, prev_x, prev_y;
	bool wander, start_found;
	
	// pick an initial starting point and remove it from the
	// vector of possible starts
	std::uniform_int_distribution<int> rand_start(0, _starts.size ()-1);
	int index = rand_start(rnd_gen);
	auto start_p = _starts[index];
	cur_x = std::get<1>(start_p);
	cur_y = std::get<0>(start_p);
	prev_x = std::get<1>(start_p);
	if (cur_y > 0)
		prev_y = std::get<0>(start_p) - 1;
	else
		prev_y = std::get<0>(start_p) + 1;
	// Add this edge to the maze set
	auto start_edge = data::edge(cur_x,cur_y,prev_x,prev_y);
	inmaze.insert({start_p, start_edge});
	// erase the start point used
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
			if (inmaze.find(start) != inmaze.end())
			{
				_starts.erase(_starts.begin()+ index);
				if (_starts.empty())
					break;
			}
			else
			{
				start_found = true;
#ifdef DEBUG
				std::cout << "starting walk from " << start <<  std::endl;
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
			data::direction dir = static_cast<data::direction>(rnd_dir(rnd_gen));
			// keep track of the previous coords used incase of a loop
			prev_x = cur_x;
			prev_y = cur_y;
			//auto& cur_cell = cells[cur_y][cur_x];
				// Edges in oposing directions
			data::edge out_edge, in_edge;
			try
			{
				switch(dir)
				{
					case data::direction::WEST:
					{
					if (cur_x == 0)
						break;
					//create the edges that go both out from here and
					//in from here
					out_edge.in_x = cur_x;
					out_edge.in_y = cur_y;
					out_edge.out_x = cur_x -1;
					out_edge.out_y = cur_y;

					cur_x = out_edge.out_x;
					cur_y = out_edge.out_y;
					// make a key for the maps
					auto key = std::make_tuple(cur_y, cur_x);
					// add this edge to the walk
					if (!inwalk.exists(key))
					{
						inwalk.add(key, out_edge);
					}
					//this edge loops back on itself
					else
					{
						throw loop_error();
					}
					// this edge joins back up with the maze
					if(inmaze.find(key) != inmaze.end())
					{
						throw maze_found(key);
					}
					break;
					}
						
					case data::direction::EAST:
					{
						if (cur_x == mmaze.width()-1)
							break;
						//create the edges that go both out from here and
					//in from here
					out_edge.in_x = cur_x;
					out_edge.in_y = cur_y;
					out_edge.out_x = cur_x + 1;
					out_edge.out_y = cur_y;

					cur_x = out_edge.out_x;
					cur_y = out_edge.out_y;
					// make a key for the maps
					auto key = std::make_tuple(cur_y, cur_x);
					// add this edge to the walk
					if (!inwalk.exists(key))
					{
						inwalk.add(key, out_edge);
					}
					//this edge loops back on itself
					else
					{
						throw loop_error();
					}
					// this edge joins back up with the maze
					if(inmaze.find(key) != inmaze.end())
					{
						throw maze_found(key);
					}
					break;

					}
					case mazer2016sp1oua::data::direction::NORTH:
					{
						//create the edges that go both out from here and
					//in from here
					out_edge.in_x = cur_x;
					out_edge.in_y = cur_y;
					out_edge.out_x = cur_x;
					out_edge.out_y = cur_y - 1;

					cur_x = out_edge.out_x;
					cur_y = out_edge.out_y;
					// make a key for the maps
					auto key = std::make_tuple(cur_y, cur_x);
					// add this edge to the walk
					if (!inwalk.exists(key))
					{
						inwalk.add(key, out_edge);
					}
					//this edge loops back on itself
					else
					{
						throw loop_error();
					}
					// this edge joins back up with the maze
					if(inmaze.find(key) != inmaze.end())
					{
						throw maze_found(key);
					}
					break;
					}
					case mazer2016sp1oua::data::direction::SOUTH:
					{
						if (cur_y == mmaze.height()-1)
							break;
						//create the edges that go both out from here and
					//in from here
					out_edge.in_x = cur_x;
					out_edge.in_y = cur_y;
					out_edge.out_x = cur_x;
					out_edge.out_y = cur_y + 1;

					cur_x = out_edge.out_x;
					cur_y = out_edge.out_y;
					// make a key for the maps
					auto key = std::make_tuple(cur_y, cur_x);
					// add this edge to the walk
					if (!inwalk.exists(key))
					{
						inwalk.add(key, out_edge);
					}
					//this edge loops back on itself
					else
					{
						throw loop_error();
					}
					// this edge joins back up with the maze
					if(inmaze.find(key) != inmaze.end())
					{
						throw maze_found(key);
					}
					break;
					}
					case mazer2016sp1oua::data::direction::INVALID:
					{
						break;
					}
				}

			/*	if (cells[cur_y][cur_x].in_maze)
				{
					data::cell* maze_start = &cells[cur_y][cur_x];
					data::cell* cur = maze_start -> parent;
					data::cell* temp;
					while(cur != nullptr)
					{
						cur -> in_walk = false;
						cur -> in_maze = true;
						temp = cur;
						cur = cur -> parent;
						temp -> parent = nullptr;
					}
					wander = false;

				}*/
			}
			catch(loop_error& le)
			{
				int count = 0;
				auto loop = std::make_tuple(prev_y, prev_x);
#ifdef DEBUG
				std::cout << "~~~~~~~~~~~~~~~Loop caught~~~~~~~~~~~~~~ " << 
					std::endl;
#endif
				inwalk.del_loop (loop);
				

			}
			catch(maze_found& mf)
			{
				inwalk.move_data (inmaze);
			}
			
		}
	}
	for (int y = 0; y < mmaze.height(); ++y)
	{
		for (int x = 0; x < mmaze.width (); ++x)
		{
			auto key = std::make_tuple(y,x);
			auto range = inmaze.equal_range(key);
			for (auto it = range.first; it != range.second; ++it)
			{
				auto& e = it -> second;
				auto dir = data::get_dir(e.in_x, e.in_y, e.out_x, e.out_y);
				cells[y][x].adjacents[int(dir)] = e;
			}
		}
	}
	mmaze.init ();
	std::cout << "Completed in: ";
}



/*bool mazer2016sp1oua::generators::wilsons::go_dir(int& cur_x, int& cur_y, 
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
*/
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


