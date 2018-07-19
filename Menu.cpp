#include "mnBr.h"
#include <ncurses.h>
#include <string.h>

char *choices[] = {"Start",
"Pause",
"Fit",
"View Raw Data",
"Configure",
"Quit",
};

Menu::Menu(WINDOW *mainWindow) {

	int LINES, COLS;
	getmaxyx(mainWindow, LINES, COLS);

	menuWin = newwin((LINES)/3, COLS/4, 0, 3*COLS/4);
	box(menuWin, 0, 0);//menuWindow;
	keypad(menuWin, TRUE);
	wrefresh(mainWindow);


	n_choices = sizeof(choices) / sizeof(char *);
	highlight = 1;
	choice = 0;

	buildMenu();

}

void Menu::buildMenu() {

	int x, y, xSize, ySize;
	getmaxyx(menuWin, ySize, xSize);

  	int yBorder = ySize/8;

	int yInterval = (ySize-yBorder-6)/7;

  	if (yInterval < 1) yInterval = 1; 
	
  	y = yInterval+yBorder;

	for (int i = 0; i < n_choices; ++i) {

		x = (xSize-strlen(choices[i]))/2;

		if (highlight == i + 1) {

			wattron(menuWin, A_REVERSE);
			mvwprintw(menuWin, y, x, "%s", choices[i]);
			wattroff(menuWin, A_REVERSE);
		} else {

			mvwprintw(menuWin, y, x, "%s", choices[i]);
		}

		y += yInterval;
	}
	
	wrefresh(menuWin);
}

int Menu::choiseMenu() {

	bool loop = true;

	while (loop) {

		halfdelay(1);
		int c = wgetch(menuWin);
		if (c != -1) {
		    switch(c) {
		       	case KEY_UP:
		       		if(highlight == 1) {
		           		highlight = n_choices;
		       		} else {
		           		--highlight;
		       			break;
		       		}
		       	case KEY_DOWN:
		       		if (highlight == n_choices) {
		           		highlight = 1;
		       		} else {
		           		++highlight;
		       			break;
		       		}
		       	case 10:
		       		choice = highlight;
		       		loop = false;
		       		break;
		       	default:

		       		break;
		    }
		}
    	buildMenu();
	}


    //sleep(2);

    return choice;
}
