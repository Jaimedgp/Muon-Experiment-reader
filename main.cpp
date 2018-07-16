#include <ncurses.h>
#include "hstgram.h"

int main (int argc, char **argv) {

	WINDOW *plotAll1, *plotAll2, *plotSelect1, *plotSelect2, *menuBar;

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

	plotSelect1 = newwin((LINES-2)/2, COLS/3, 2, 2*COLS/3);
	box(plotSelect1, 0, 0);
	wrefresh(plotSelect1);

    mvwprintw(plotSelect1, 5, 5, "Elapsed Time: 200");
    mvwprintw(plotSelect1, 10, 5, "Number of Muons: 100");
    mvwprintw(plotSelect1, 15, 5, "Muonn Rate (per second): 3");
    mvwprintw(plotSelect1, 20, 5, "Muon Decays: 4");
    mvwprintw(plotSelect1, 25, 5, "Decay Rate (per minute): 1");
    wrefresh(plotSelect1);
	
	plotSelect2 = newwin((LINES-2)/2, COLS/3, 2+(LINES-2)/2, 2*COLS/3);
	box(plotSelect2, 0, 0);
	wrefresh(plotSelect2);

	Histogram h(argc, argv, plotAll1);

	for (int i=0; i<10; ++i) {
        h.drawIncrement(i);
	}

	Histogram j(argc, argv, plotAll2);

	for (int i=0; i<10; ++i) {
        j.drawIncrement(i);
	}

	getch();

    endwin();
	return 0;
}
