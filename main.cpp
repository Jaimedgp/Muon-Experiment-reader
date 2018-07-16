#include <ncurses.h>
#include "hstgram.h"

int main (int argc, char **argv) {

	WINDOW *plotAll1, *plotAll2, *plotSelect, *menuBar;

	noecho();
	initscr();			
	cbreak();
	keypad(stdscr, TRUE);			

	refresh();

	plotAll1 = newwin((LINES-2)/2, 2*COLS/3, 2, 0);
	box(plotAll1, 0, 0);
	wrefresh(plotAll1);

	plotAll2 = newwin((LINES-2)/2, 2*COLS/3, 2+(LINES-2)/2, 0);
	box(plotAll2, 0, 0);
	wrefresh(plotAll2);

	plotSelect = newwin(LINES-2, COLS/3, 2, 2*COLS/3);
	box(plotSelect, 0, 0);
	wrefresh(plotSelect);
	
	Histogram h(argc, argv, plotAll1);

	for (int i=0; i<10; ++i) {
        h.drawIncrement(i);
	}

	getch();

    endwin();
	return 0;
}
