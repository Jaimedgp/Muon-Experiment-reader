#include <ncurses.h>
#include "hstgram.h"
#include "mnBr.h"

int main (int argc, char **argv) {

	WINDOW *muonDcysLy, *muonLy, *menuLy, *showDataLy;

	noecho();
	initscr();			
	cbreak();
	keypad(stdscr, TRUE);			

	refresh();

	muonDcysLy = newwin(2*(LINES)/3, 3*COLS/4, 0, 0);
	box(muonDcysLy, 0, 0);
	wrefresh(muonDcysLy);

	muonLy = newwin((LINES)/3, COLS, 2*(LINES)/3, 0);
	box(muonLy, 0, 0);
	wrefresh(muonLy);

	menuLy = newwin((LINES)/3, COLS/4, 0, 3*COLS/4);
	box(menuLy, 0, 0);

    Menu mn(menuLy);
    
    wrefresh(menuLy);
	
	showDataLy = newwin((LINES)/3, COLS/4, (LINES)/3, 3*COLS/4);
	box(showDataLy, 0, 0);

    mvwprintw(showDataLy, 5, 5, "Elapsed Time: 200");
    mvwprintw(showDataLy, 7, 5, "Number of Muons: 100");
    mvwprintw(showDataLy, 9, 5, "Muonn Rate (per second): 3");
    mvwprintw(showDataLy, 11, 5, "Muon Decays: 4");
    mvwprintw(showDataLy, 13, 5, "Decay Rate (per minute): 1");

	wrefresh(showDataLy);

	int values[20] = {0,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9};

	Histogram h(argc, argv, muonDcysLy, 10, 20, values);

	sleep(4);

	for (int i=0; i<20; ++i) {
        h.drawIncrement(i);
	}

	int y, x;
	getmaxyx(muonLy, y, x);

	int www = (x-(x/15))/4;

	Histogram j(argc, argv, muonLy, 10, www, values);

	for (int i=0; i<www; ++i) {
        j.drawIncrement(i);
	}

	getch();

    endwin();

	return 0;
}
