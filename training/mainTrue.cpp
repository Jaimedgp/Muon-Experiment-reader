/**
 * Main script
 *
 */

#include <ncurses.h>
#include <iostream>
#include "mnBr.h"

//----------------------------------
//    	 FUNCTIONS
//----------------------------------

void menuOptions();

int main (int argc, char **argv) {
    
    noecho();
    initscr();
    cbreak();

    // Create Menu Window
    Menu menu (stdscr);

    endwin();

    return 0;
}

void menuOptions() {

	bool initProgram = true;

	while (initProgram) {
		option = choiseMenu();

		if (option != -1) {
			switch (option) {
				case 1:
					std::thread
			}
		}
	}
}