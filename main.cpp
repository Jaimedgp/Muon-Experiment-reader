#include "Menu.h"
#include "MuonReader.h"

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

    WINDOW *muonDcysLy, *muonPerMinutLy, *showDataLy;
    MuonReader *muonRead;
    bool runProgram, readUSB;

    void createLy (WINDOW *mainWin);

    void menuOptions(int option);

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

int main () {

    noecho();
    initscr();          
    cbreak();
    refresh();
    curs_set(0);

    runProgram = true;

    createLy(stdscr);

    Menu mn = Menu(stdscr);
    MuonReader muonRead = MuonReader (muonDcysLy, muonPerMinutLy, showDataLy);

    do {

    	int c = wgetch(mn.menuWin);

    	if (c != -1) {
    		int option = mn.choiseMenu(c);
    		menuOptions(option);
    	} else {
    		if (readUSB) {
    			muonRead.collectData();
    		}
    	}


    } while(runProgram);



    //-------------------------------------------

    endwin();

    return 0;

}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

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

    void menuOptions(int option) {

    	if (option != -1){
    		switch(option) {
                case 1:
                	muonRead->startReading();
                    readUSB = true;
                    break;
                case 2:
                    readUSB = false;
                    break;
                case 4:
                    muonRead->save();
                    break;
                case 6:
                    readUSB = false;
                    runProgram = false;
                    break;
                default:
                    break;
            }
    	}
    }