/**
 *
 *
 */

#include "ShowData.h"

ShowData::ShowData(WINDOW* mainWindow) {

	//int LINES, COLS;
	//getmaxyx(ncursesWin, LINES, COLS);

	/* MUON DECAY DATA */

	// Window for Muon Decay histogram
	muonDcysLy = newwin(2*(LINES)/3, 3*COLS/4, 0, 0);
	box(muonDcysLy, 0, 0);
	wrefresh(muonDcysLy);

	int muonDcayVlue[20];

	// MuonDecay histogram
	Histograms muonDcayHis(muonDcysLy, 10, 20, muonDcayVlue);

	

	/* MUON PER MINUTE DATA */

	// Window for Muon Decay histogram
	muonPerMinutLy = newwin((LINES)/3, COLS, 2*(LINES)/3, 0);
	box(muonPerMinutLy, 0, 0);
	wrefresh(muonPerMinutLy);


	// number of columns to occupay all window
	int numcolumns = (COLS-(COLS/15))/4;
	int muonPerMinutVlue[numcolumns];

	// MuonDecay histogram
	Histograms muonPerMinutHis (muonPerMinutLy, 10, numcolumns, muonPerMinutVlue);
}

void ShowData::addMuonDecay (int elapse) {

	for (int i = 1; i<20; ++i) {

		if (elapse < (600*i)) {
			muonDcayHis.drawIncrement(i-1);
			break;
		}
	}
}