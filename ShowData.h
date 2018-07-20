/**
 *
 *
 */

#ifndef ShowData_h
#define ShowData_h

#include <ncurses.h>
#include "Histograms.h"

class ShowData {

	public:
		ShowData (WINDOW*);

		void addMuonDecay (int);

		WINDOW *muonDcysLy;
		int muonDcayVlue[];

		WINDOW *muonPerMinutLy;
		int muonPerMinutVlue[];
	
};

#endif