/**
 *
 * MENU
 *
 * @author Jaimedgp
 * @version 1.0
 */

#include <ncurses.h>
#include <string.h>

#include "Menu.h"

char *choices[] = {"Start",
				"Pause",
				"Reset",
				"Save",
				"Fit",
				"Quit",
};

Menu::Menu(WINDOW *mainWindow) {

	int LINES, COLS;
	getmaxyx(mainWindow, LINES, COLS);

	menuWin = newwin((LINES)/3, COLS/4, 0, 3*COLS/4);
	box(menuWin, 0, 0);//menuWindow;
	keypad(menuWin, TRUE);
	nodelay(menuWin, TRUE);
	wrefresh(mainWindow);

	n_choices = sizeof(choices) / sizeof(char *);
	highlight = 1;
	choice = 0;

	buildMenu();
}

void Menu::buildMenu() {

	int x, y, xSize, ySize;
	getmaxyx(menuWin, ySize, xSize);

    if (ySize < (2*n_choices+1)) {
        int error =-1;
    }

    int yStart = (ySize - 2*n_choices) / 2;
    
	for (int i = 0; i < n_choices; ++i) {

		x = (xSize-strlen(choices[i]))/2;

		if (highlight == i + 1) {

			wattron(menuWin, A_REVERSE);
			mvwprintw(menuWin, yStart, x, "%s", choices[i]);
			wattroff(menuWin, A_REVERSE);
		} else {

			mvwprintw(menuWin, yStart, x, "%s", choices[i]);
		}

		yStart += 2;
	}
	
	wrefresh(menuWin);
}

int Menu::choiseMenu(int c) {

    choice = -1;

	switch(c) {
	   	case KEY_UP:
	 		if(highlight == 1) {
	       		
	      		highlight = n_choices;
	  		} else {
		           		
	       		--highlight;
            }
            break;
        
        case KEY_DOWN:
            if (highlight == n_choices) {
                
                highlight = 1;
            } else {
                
                ++highlight;
            }
            break;
        
        case 10:
                choice = highlight;
                break;
            default:
                break;
    }
        
    buildMenu();

    return choice;
}
