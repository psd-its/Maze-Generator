#include "sidewinder.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

void mazer2016sp1oua::generators::sidewinder::generate (void)
{
	std::cout << "Generating..." << std::endl;
    int y, x, draw = 0;
	// Traverse the maze
    for (y = 0; y < mymaze.height(); ++y)
    {
        for (x = 0; x < mymaze.width(); ++x)
        {
            // Top row treated specially
            if (y == 0)
            {
                // right hand edge of the maze
                if (x == mymaze.width() -1)
                {
                    continue;
                }
                // go east along the top row
                else
                {
                    set_wall(y, x, generators::winder::RIGHT);
                }
            }
			// decide how many cells to draw right
			if (draw < 0 && y > 0)
			{
				draw = run_size();
				// Decide the point to carve up
				int i = x + up_point(draw);
#ifdef DEBUG
				std::cout <<"Y: "<< y << " X: " << i << std::endl;
#endif
				// The up carve will be inside the maze
				if (i < mymaze.width()-1)
				{
					/*if (y < 1)
						continue;*/
					set_wall(y, i, generators::winder::UP);
				}
				// The up carve would be outside the maze so set it to the
				// right hand edge
				else
				{
					set_wall(y, mymaze.width()-1, generators::winder::UP);
				}
				
			}
			// draw the edge heading east
			if (draw >= 0)
			{
				// if draw is 0 leave an empty cell
				if (draw != 0 && x < mymaze.width() -1)
					set_wall(y, x, generators::winder::RIGHT);
				// Decrement the count of how many cells to draw
				--draw;
				
			}
			// We are at the end of the maze
			else if (y == mymaze.height() -1 && x == mymaze.width()-1)
				{
					break;
				}
		    
				
			
        }
		draw = -1;
    }
	std::cout << "Completed in ";
	mymaze.init ();
}

void mazer2016sp1oua::generators::sidewinder::set_wall(int y, int x,
                                                       generators::winder dir)
{
    auto& cells = mymaze.get_cells ();
    auto& cur_cell = cells[y][x];
    data::edge out_edge, in_edge;
    if ( dir == generators::winder::RIGHT)
    {
        //create the edges that go both directions
        out_edge.in_x = in_edge.out_x = x;
        out_edge.in_y = in_edge.out_y = y;
        out_edge.out_x = in_edge.in_x = x + 1;
        out_edge.out_y = in_edge.in_y = y;
        x = out_edge.out_x;
        y = out_edge.out_y;
        // add edges to appropriate cells
        cur_cell.adjacents[int(mazer2016sp1oua::data::direction::EAST)] = 
            out_edge;
        auto & alt_cell = cells[y][x];
        alt_cell.adjacents[int(mazer2016sp1oua::data::direction::WEST)] =
            in_edge;
        return;

    }
    else if (dir == generators::winder::UP)
    {
        //create the edges that go both directions
        out_edge.in_x = in_edge.out_x = x;
        out_edge.in_y = in_edge.out_y = y;
        out_edge.out_x = in_edge.in_x = x;
        out_edge.out_y = in_edge.in_y = y - 1;
        x = out_edge.out_x;
        y = out_edge.out_y;
        // add edges to appropriate cells
        cur_cell.adjacents[int(mazer2016sp1oua::data::direction::NORTH)] = 
            out_edge;
        auto & alt_cell = cells[y][x];
        alt_cell.adjacents[int(mazer2016sp1oua::data::direction::SOUTH)] =
            in_edge;
        return;
    }
}