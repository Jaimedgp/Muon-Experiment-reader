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

class MuonReader {

	public:
		bool reading;
		time_t clock;
		int counter;

		std::string nameOfDevice;

		std::vector<int> cronometer;
    	std::vector<time_t> timer;

    	MuonReader ( std::string );
    	void readLoop ();
    	
    	int readUSB ();
    	int hex2Dec (char*);
    	int* clasifiedData (int); 
};

#endif