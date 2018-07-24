#ifndef DataLy_h
#define DataLy_h
#include <ncurses.h>

class DataLy {

	public:
		DataLy(WINDOW *);

		void printElapsTime(int );
		void printNumMuon(int );
		void printMuonRate();
		void printMuonDcy();
		void printDcyRate();

        int time, numberMuons, muonDcy;


	//private:
		WINDOW *cursesWin;

		int xBrdrLabel, y, yInterval;
};

#endif
