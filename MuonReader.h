/**
 *
 */

#ifndef MuonReader_h
#define MuonReader_h

#include <ncurses.h>
#include <iostream>
#include <stdlib.h>

#include <vector> // use std::vector
#include <time.h> // get seconds
#include <sstream> // converto hex >> dec
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function

#include "Histograms.h"
#include "DataLy.h"

class MuonReader {
	public:
		MuonReader (WINDOW *muonDcysLy, WINDOW *muonPerMinutLy, WINDOW *showDataLy);

        void Reset();
		void collectData ();
		void startReading ();
		void save();

		std::vector<int> elapsed;
    	std::vector<time_t> clocks;

    	std::string nameOfDevice;
    	int fileAdress;
    	time_t timeinit;
    	time_t seconds;

	private:

		int hex2Dec (char* outputPort);
		char clasifiedData(char *buf);

		int counterSec;
		int counterMin;
        int minute;

		Histograms muonDcysHis = Histograms();
		Histograms muonPerMinutHis = Histograms();
		DataLy dataLy = DataLy();
};

#endif
