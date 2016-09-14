/**
 * @file constants.h contains global constants for the application.
 * Created by Paul Miller as part of the assignment 1 solution for
 * CPT323 - Object Oriented Programming Using C++, study period 1, 2016.
 **/
#pragma once

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

/**
 * the base namespace for this project
 **/
namespace mazer2016sp1oua
{
	/**
	 * namespace that holds all constants used by the system
	 **/
	namespace constants
	{
		/**
		 * a global int constant for the application representing an
		 * error state
		 **/
		const int ERROR = -1;
		/**
		 * defines the number of parameters passed in when generating a
		 * maze where no seed is provided
		 **/
		const int NOSEED = 2;

		/**
		 * the default width for a maze
		 **/
		const unsigned DEFAULT_WIDTH = 10;

		/**
		 * default height for a maze
		 **/
		const unsigned DEFAULT_HEIGHT = 10;

		/**
		 * minimum value for width or height
		 **/
		const int MIN_DIM = 2;

		/**
		 * maximum value for width or height
		 **/
		const int MAX_DIM = 5000;

		/**
		 * constant for the start of the maze matrix
		 **/
		const int START = 0;
		/**
		 * Walk is unlikely to complete to clear it and start again
		 **/
		const int ERROR_MAX = 300;

		/**
		 * Huristic to use
		 **/
		enum class huristic
		{
			EUCLIDEAN, MANHATTEN
		};

		


	}
}
