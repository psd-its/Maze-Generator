//#pragma once
#include "action.h"
#include "../generators/binary_gen.h"
#include "../generators/wilsons.h"
#include "../data/maze.h"
#include "../solvers/bfs_solver.h"
#include "../generators/sidewinder.h"
#include "../solvers/dijkstra.h"
#include "../solvers/astar.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

/**
 * @file action.cpp contains implementations of concrete child classes of 
 * the action class which represent a request to do something from the 
 * command line.
 **/

/**
 * @param m the maze data structure to initialise and write the generated
 * maze to.
 **/
//using namespace mazer2016sp1oua::args;
mazer2016sp1oua::data::maze& 
mazer2016sp1oua::args::generate_action::do_action(mazer2016sp1oua::data::maze& m)
{
    
    switch(gen_type)
    {
        // generate using binary tree
        case gen_algorithm::BINARY:
        {
	        generators::binary_gen generator(m, _width, _height, _seed);
	        generator.generate();
            break;
        }
            // generate using wilsons walk
        case gen_algorithm::WILLS:
        {
	        generators::wilsons generator(m, _width, _height, _seed);
	        generator.generate();
            break;
        }
            // generate using sidewinder
        case gen_algorithm::SIDE:
        {
            generators::sidewinder generator(m, _width, _height, _seed);
	        generator.generate();
            break;
        }
    }
#ifdef DEBUG
	//output the adjacency lists for the maze
	std::cerr << m;
#endif //DEBUG
	return m;
}

/**
 * perform a save action - save a maze either as a binary or svg file
 **/
mazer2016sp1oua::data::maze&
mazer2016sp1oua::args::save_action::do_action(mazer2016sp1oua::data::maze &m)
{
	/**
	 * test if the maze has been initialized yet and if it has not 
	 * throw an exception
	 **/
	if(m.initialized())
	{
		//save a binary file
		if(_type == save_type::BINARY)
		{
			if(!m.save_binary(_name))
			{
				std::ostringstream oss;
				oss << "There was an error saving the binary file "
					<< _name << std::endl;
				throw action_failed(oss.str());
			}
		}
		else
		{
			//save an svg file
			if(!m.save_svg(_name))
			{
				std::ostringstream oss;
				oss << "There was an error saving the svg file " 
					<< _name << std::endl;
				throw action_failed(oss.str());
			}
		}
	}
	else
	{
		//the maze is not initialized
		std::ostringstream oss;
		oss << "Error: the maze is not yet initialized. " 
			<< "I can't save a non-existent maze." << std::endl;
		throw action_failed(oss.str());
	}
	return m;
}

mazer2016sp1oua::data::maze & 
mazer2016sp1oua::args::load_action::do_action(mazer2016sp1oua::data::maze & m)
{
	if(!m.load_binary(_name))
	{
		std::ostringstream oss;
		oss << "There was an error loading the binary file " 
			<< _name << std::endl;
		throw action_failed(oss.str());
	}
	return m;
}

mazer2016sp1oua::data::maze&
mazer2016sp1oua::args::solve_action::do_action(mazer2016sp1oua::data::maze& m)
{
	if (!m.initialized())
	{
		//the maze is not initialized
		std::ostringstream oss;
		oss << "Error: the maze is not yet initialized. " 
			<< "I can't solve a non-existent maze." << std::endl;
		throw action_failed(oss.str());
	}
	switch(_type)
	{
		case solve_type::BFS:
		{
            // create a new instance of bfs solver
			mazer2016sp1oua::solvers::Solve_bfs bfs = 
							mazer2016sp1oua::solvers::Solve_bfs(m);
	        // solve the maze
		    bfs.solve();
			break;
		}
		case solve_type::ASTAR_E:
		{
			mazer2016sp1oua::solvers::astar ae = 
							mazer2016sp1oua::solvers::astar(m, 
							                 constants::huristic::EUCLIDEAN);
			ae.solve();
			break;
		}
		case solve_type::ASTAR_M:
		{
			mazer2016sp1oua::solvers::astar am = 
							mazer2016sp1oua::solvers::astar(m, 
							                 constants::huristic::MANHATTEN);
			am.solve();
			break;
		}
		case solve_type::DIJ:
		{
			// create a new instance of dijkstra
			mazer2016sp1oua::solvers::dijkstras dij = 
				mazer2016sp1oua::solvers::dijkstras(m);
			// solve the maze
			dij.solve();
			break;
		}


	}
	return m;

}

