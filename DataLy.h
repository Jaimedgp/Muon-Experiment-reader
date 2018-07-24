#ifndef DataLy_h
#define DataLy_h
#include <ncurses.h>

class DataLy {

	public:
		DataLy(WINDOW *);

		void printElapsTime(int);
		void printNumMuon(int);
		void printMuonRate(double);
		void printMuonDcy(int);
		void printDcyRate(double);


	private:
		WINDOW *cursesWin;

		int xBrdrLabel, y, yInterval;
};

#endif