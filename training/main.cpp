#include <ncurses.h>
#include <iostream>
#include <thread>

#include "hstgram.h"
#include "mnBr.h"
#include "dataLy.h"

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

	DataLy dtly(showDataLy);

	wrefresh(showDataLy);

	int values[20];

	Histogram h(argc, argv, muonDcysLy, 10, 20, values);

	sleep(4);

	int y, x;
	getmaxyx(muonLy, y, x);

	int www = (x-(x/15))/4;

	Histogram j(argc, argv, muonLy, 10, www, values);

	sleep(2);

	std::thread first (mn.choiseOne);

	//std::thread second ();

    endwin();

	return 0;
}
