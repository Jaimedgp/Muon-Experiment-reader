#include <ncurses.h>
#include "hstgram.h"

int main (int argc, char **argv) {

	WINDOW *plotAll1, *plotAll2, *plotSelect1, *plotSelect2, *menuBar;

	noecho();
	initscr();			
	cbreak();
	keypad(stdscr, TRUE);			

	refresh();

	plotAll1 = newwin(2*(LINES)/3, 3*COLS/4, 0, 0);
	box(plotAll1, 0, 0);
	wrefresh(plotAll1);

	plotAll2 = newwin((LINES)/3, COLS, 2*(LINES)/3, 0);
	box(plotAll2, 0, 0);
	wrefresh(plotAll2);

	plotSelect1 = newwin((LINES)/3, COLS/4, 0, 3*COLS/4);
	box(plotSelect1, 0, 0);

    mvwprintw(plotSelect1, 2, 10, "Start");
    mvwprintw(plotSelect1, 5, 10, "Pause");
    mvwprintw(plotSelect1, 8, 10, "Fit");
    mvwprintw(plotSelect1, 11, 10, "View Raw Data");
    mvwprintw(plotSelect1, 14, 10, "Configure");
    mvwprintw(plotSelect1, 17, 10, "Quit");

    wrefresh(plotSelect1);
	
	plotSelect2 = newwin((LINES)/3, COLS/4, (LINES)/3, 3*COLS/4);
	box(plotSelect2, 0, 0);

    mvwprintw(plotSelect2, 5, 5, "Elapsed Time: 200");
    mvwprintw(plotSelect2, 7, 5, "Number of Muons: 100");
    mvwprintw(plotSelect2, 9, 5, "Muonn Rate (per second): 3");
    mvwprintw(plotSelect2, 11, 5, "Muon Decays: 4");
    mvwprintw(plotSelect2, 13, 5, "Decay Rate (per minute): 1");

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
