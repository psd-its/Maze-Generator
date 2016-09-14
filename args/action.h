#pragma once
#include <iostream>
#include <exception>
#include <sstream>
#include "../constants/constants.h"
#include <chrono>

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

namespace mazer2016sp1oua
{
    namespace data
    {
        /** 
         * forwards declaration required to avoid a recursive include
         **/
        class maze;
    }
    namespace args
    {
        enum class gen_algorithm
        {
            BINARY,
            WILLS,
            SIDE
        };
        /**
         * abstract class that represents all types of actions that can
         * be requested from the command line.
         **/
        class action
        {
            public:
                /**
                 * pure virtual function that must be implemented in each
                 * child class to describe how to perform the action 
                 * specified on a maze.
                 * @return a reference to the maze passed in.
                 **/
                virtual data::maze & 
                    do_action(data::maze &) = 0;
        };

        /**
         * exception that may be thrown from any do_action() function to
         * indicate that that action failed.
         **/
        class action_failed : public std::exception
        {
            /**
             * message to be returned from this exception
             **/
            std::string _message;

            public:
            /**
             * constructor - simply assigns the message
             **/
            action_failed(const std::string message) 
                : _message(message) {}

            /**
             * return the message to be displayed. After this, 
             * the message is no longer valid in this class as it is
             * returned by move.
             **/
            const char * what(void)
            {
                return std::move(_message.c_str());
            }

	};
     
        /**
         * represents a request to generate a maze
         **/
        class generate_action : public action
        {
            /**
             *  the seed used to start the random number generator or 
             *  @ref constants::ERROR if it has not been
             *  initialized yet.
             **/
            int _seed;

            /**
             * the width of the maze to generate
             **/
            unsigned _width;

            /**
             * the height of the maze to generate
             **/
            unsigned _height;

            /**
             * Generation algorithm to be used
             **/
            gen_algorithm gen_type;

            public: 

            /**
             * default constructor - required to insert actions into an
             * stl container.
             **/
            generate_action(void){}

            /**
             * creates a generate_action based on a width and height
             * being specified
             **/
            generate_action(unsigned width,unsigned height,
                            gen_algorithm type) 
                : _seed(std::chrono::system_clock::now()
                .time_since_epoch() / 
                std::chrono::milliseconds(1)*-1), 
                _width(width), _height(height), gen_type(type)
            {
            }

            /**
             * creates a generate_action based on the seed, width and 
             * height being specified
             **/
            generate_action(int seed, unsigned width, unsigned height,
                            gen_algorithm type)
                : _seed(
                        seed == constants::ERROR ? 
                        std::chrono::system_clock::now()
                        .time_since_epoch() / 
                        std::chrono::milliseconds(1) : seed), 
                    _width(width), _height(height), gen_type(type) 
            {
            }

            /**
             * creates a generate_action for when only the seed is 
             * specified
             **/
            generate_action(int seed, gen_algorithm type) : _seed(seed), 
            _width(constants::DEFAULT_WIDTH), 
            _height(constants::DEFAULT_HEIGHT),
                gen_type(type)
            {
            }

            virtual data::maze & do_action(data::maze &);
        };

        /**
         * defines a load action specified from the command line
         **/
        class load_action : public action
        {
            /**
             * the file name of the file to load from disk
             **/
            std::string _name;
            public:
            /**
             * constructor - just assigns the file name; the rest of the 
             * work will be done later.
             **/
            load_action(const std::string & name) : _name(name)
            {
            }

            virtual data::maze& do_action(data::maze &);

        };

        /**
         * how do we want to save a file? Binary or Svg? 
         **/
        enum class save_type
        {
            ///save the file as binary
            BINARY, 
            ///save the file as svg
            SVG
        };

        /**
         * models a save request passed in from the command line
         **/
        class save_action : public action
        {
            /**
             * the type of saving to be done
             **/
            save_type _type;

            /**
             * the name of the file to save to
             **/
            std::string _name;

            public:
            /**
             * constructor - simply assigns the type of save and the 
             * file to save to
             **/
            save_action(save_type type, const std::string & name) 
                : _type(type), _name(name)
            {
            }
            virtual data::maze & do_action(data::maze &);
        };

	/**
         * Which solving algorithm to use
         **/
        enum class solve_type
        {
            // Breadth First Search
            BFS,
            // A star with euclidian distance
            ASTAR_E,
            // A star using manhattan distance
            ASTAR_M,
            // Path finding using dijkstras
            DIJ
        };

        /**
         * Models a solving algorithm
         **/
        class solve_action : public action
        {
            // which solving algorithm to use
            solve_type _type;

            public:
                // Constructor takes the algorithm used as a param
                solve_action(solve_type type) : _type(type){}

                //
                virtual data::maze & do_action(data::maze &);

        };
    }
}

