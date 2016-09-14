#include "../data/maze.h"
#include <random>

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
    namespace generators
    {
        enum class winder
        {
            RIGHT, UP
        };
        
        class sidewinder
        {
            data::maze& mymaze;
            std::mt19937 _gen;
            // enum up or right
            winder _choose;  
            std::uniform_int_distribution<int> _len;
            public:
               
                sidewinder(data::maze& m, int width, int height, int seed)
                    : mymaze(m), _gen(seed), _len(0, 5)
                {
                    mymaze.height(height);
                    mymaze.width(width);
                    //clear all connections
                    mymaze.clear();
            
                    //_choose = static_cast<winder>(_dir(_gen));
                    std::cout << "seed for this generator is: " <<
                    seed << std::endl;
                }
                // Generate a maze
                void generate (void);
                // Set the edges
                void set_wall(int, int, winder);
                
                // inline function for picking the length of a run
                int run_size(void)
                {
                    return _len(_gen);
                }
				int up_point(int n)
				{
					std::uniform_int_distribution<int> up(0, n);
					return up(_gen);
				}
				
        };

        
    }
}