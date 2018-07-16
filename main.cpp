#include <ncurses.h>
#include "hstgram.h"

int main (int argc, char **argv) {

	WINDOW *plotAll, *plotSelect, *menuBar;

	noecho();
	initscr();			
	cbreak();
	keypad(stdscr, TRUE);			

	refresh();

	plotAll = newwin(LINES, COLS, 0, 0);
	box(plotAll, 0, 0);
	wrefresh(plotAll);

	//plotSelect = newwin(LINES-2, COLS/3, 2, 0);
	//box(plotSelect, 0, 0);
	//wrefresh(plotSelect);
	
	Histogram h(argc, argv, plotAll) ;

	for (int i=0; i<10; ++i) {
		h.drawValues(i);
	}

	getch();

	return 0;
}
