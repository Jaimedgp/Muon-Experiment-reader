#include <ncurses.h>

#include "Menu.h"
#include "Histograms.h"
//#include "DataLy.h"

void createLy (WINDOW *);

WINDOW *muonDcysLy, *muonPerMinutLy, *showDataLy;

int main () {
	
	noecho();
	initscr();			
	cbreak();
	refresh();

	createLy(stdscr);

	Menu mn(stdscr);

	Histograms muonDcysHis(muonDcysLy, 10, 20);

	int numColmns = (COLS-(COLS/15))/4;

	Histograms muonPerMinutHis(muonPerMinutLy, 10, numColmns);

	muonDcysHis.passTime(2);

	getch();

	endwin();

}

void createLy (WINDOW *mainWin) {

	muonDcysLy = newwin(2*(LINES)/3, 3*COLS/4, 0, 0);
	box(muonDcysLy, 0, 0);
	wrefresh(muonDcysLy);

	muonPerMinutLy = newwin((LINES)/3, COLS, 2*(LINES)/3, 0);
	box(muonPerMinutLy, 0, 0);
	wrefresh(muonPerMinutLy);

	showDataLy = newwin((LINES)/3, COLS/4, (LINES)/3, 3*COLS/4);
	box(showDataLy, 0, 0);
	wrefresh(showDataLy);
}