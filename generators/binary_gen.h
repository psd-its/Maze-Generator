//#include <random>
#include <iostream>
#include "../data/maze.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

/**
 * containing namespace for all the application
 **/
namespace mazer2016sp1oua
{
    /* namespace for all generators - we will have a few different types 
     * of generators in the second assignment
     */
    namespace generators
    {
        /**
         * we can only go down or right for the binary generator
         **/
        enum class binary_dir
        {
            DOWN, RIGHT
        };

        /**
         * implements the binary tree generator for this application
         **/
        class binary_gen
        {
            //a reference to the one maze in the system that we will manipulate
            data::maze & mymaze;
            //our random number generator
            std::mt19937 rnd_gen;

            public:
                /**
                 * constructor for the generator - sets the width and height for the
                 * maze and clears the maze so there are no connections.
                 **/
                binary_gen(data::maze& m, int _width, int _height, int _seed)
                    : mymaze(m), rnd_gen(_seed)
                    {
                        mymaze.height(_height);
                        mymaze.width(_width);
                        //clear all connections
                        mymaze.clear();
                        std::cout << "seed for this generator is: " <<
                            _seed << std::endl;
                    }
                /**
                 * function that implements the generation of the maze
                 **/
                void generate(void);
        };
    }
}
