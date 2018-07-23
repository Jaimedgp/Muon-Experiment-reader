/**
 *
 *
 */

#ifndef MuonReader_h
#define MuonReader_h

#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function

#include <vector> // use std::vector
#include <time.h> // get seconds
#include <sstream> // converto hex >> dec

#include <ncurses.h>

class MuonReader {

	public:
		time_t clock;
		int counterS;
		int elapse;
		int counterMin;
		bool reading;

		std::string nameOfDevice;

		std::vector<int> cronometer;
    	std::vector<time_t> timer;

    	MuonReader (std::string );

    	char readUSB ();
    	int hex2Dec (char*);
    	char clasifiedData (int); 
};

#endif