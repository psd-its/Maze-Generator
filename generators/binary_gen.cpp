#include "binary_gen.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

/**
 * iterates over the maze and at each point flips a coin. We will either draw
 * an edge going downwards or right. 
 **/
void mazer2016sp1oua::generators::binary_gen::generate(void)
{
	// there are only two values we are interested in 0 or 1 to represent the
	// coin flip.
	std::uniform_int_distribution<int> w_dist(0, 1);
	int w_count, h_count;
	//iterate over the maze
	for(h_count = 0; h_count < mymaze.height(); ++h_count)
	{
		for(w_count = 0; w_count < mymaze.width(); ++w_count)
		{
			// flip the coin and store that value as a direction
			binary_dir dir = static_cast<binary_dir>(w_dist(rnd_gen));
			auto & cells = mymaze.get_cells();
			auto & cur_cell = cells[h_count][w_count];
			data::cell * other_cell=nullptr;
			//while we don't have a successful coin flip
			while(!other_cell)
			{
				data::edge out_edge, in_edge;

				//if the flip results in going down
				if(dir == binary_dir::DOWN)
				{
					//check for out of bounds
					if(h_count < mymaze.height() - 1)
					{
						//create the edges that go both out from here and
						//in from here
						out_edge.in_x = in_edge.out_x = w_count;
						out_edge.in_y = in_edge.out_y = h_count;
						out_edge.out_x = in_edge.in_x = w_count;
						out_edge.out_y = in_edge.in_y = h_count + 1;
						//grab the cell at the other end of this edge
						other_cell = & cells[out_edge.out_y][out_edge.out_x];
						//set the out_edge and the in_edge in our maze
						cur_cell.adjacents[int(data::direction::SOUTH)]
							= out_edge;
						other_cell->adjacents[int(data::direction::NORTH)]
							= in_edge;
					}
				}
				else
				{
					//horizontal edge
					if(w_count < mymaze.width() - 1)
					{
						//construct the outgoing and incoming edges
						out_edge.in_x = in_edge.out_x = w_count;
						out_edge.in_y = in_edge.out_y = h_count;
						out_edge.out_x = in_edge.in_x = w_count + 1;
						out_edge.out_y = in_edge.in_y = h_count;
						//set the edges in our maze
						other_cell = & cells[out_edge.out_y][out_edge.out_x];
						cur_cell.adjacents[int(data::direction::WEST)]
							= out_edge;
						other_cell->adjacents[int(data::direction::EAST)]
							= in_edge;
					}
				}
				dir = static_cast<binary_dir>(w_dist(rnd_gen));
				//no need to draw an edge from the bottom right of the maze
				//in fact it would be out of bounds so we stop here.
				if(w_count == mymaze.width() - 1
				   && h_count == mymaze.height() - 1)
				{
					//we have finished generating the maze and so set it to
					//the initialised state
					mymaze.init();
					break;
				}
			}
		}
	}
}
