#include <thread>
#include <panel.h>

#include "Menu.h"
#include "MuonReader.h"
#include "ErrorMessage.h"

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

    WINDOW *muonDcysLy, *muonPerMinutLy, *showDataLy;
    PANEL *mainPanel[4];
    MuonReader *muonRead;

    std::thread USB;

    bool runProgram, readUSB, inPaused;
    time_t initPaused;

    void USBloop();

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
    inPaused = false;

    createLy(stdscr);

    Menu mn = Menu(stdscr);
    mainPanel[3] = new_panel(mn.menuWin);

    MuonReader mR = MuonReader (muonDcysLy, muonPerMinutLy, showDataLy);
    ErrorMessage();
    refresh();
    muonRead = &mR;
    
    USB = std::thread (USBloop);
    USB.detach();
    
    do {

    	int c = wgetch(mn.menuWin);

    	if (c != -1) {
    		int option = mn.choiseMenu(c);
    		menuOptions(option);
    	} 


    } while(runProgram);



    //-------------------------------------------

    endwin();

    return 0;

}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

    void USBloop () {

        while (1) {
            if (readUSB) {
                muonRead -> collectData();
            }
        }
    }

   void createLy (WINDOW *mainWin) {

        muonDcysLy = newwin(2*(LINES)/3, 3*COLS/4, 0, 0);
        box(muonDcysLy, 0, 0);
        wrefresh(muonDcysLy);
        mainPanel[0] = new_panel(muonDcysLy);

        muonPerMinutLy = newwin((LINES)/3, COLS, 2*(LINES)/3, 0);
        box(muonPerMinutLy, 0, 0);
        wrefresh(muonPerMinutLy);
        mainPanel[1] = new_panel(muonPerMinutLy);

        showDataLy = newwin((LINES)/3, COLS/4, (LINES)/3, 3*COLS/4);
        box(showDataLy, 0, 0);
        wrefresh(showDataLy);
        mainPanel[2] = new_panel(showDataLy);
    }

    void menuOptions(int option) {

    	if (option != -1){
    		switch(option) {
                case 1:
                	muonRead->startReading();
                    if (!inPaused) {
                        muonRead -> timeinit = time(NULL);
                        muonRead -> seconds = time(NULL);
                    } else {
                        muonRead -> timeinit += (time(NULL) - initPaused);
                    }
                    readUSB = true;
                    break;
                case 2:
                    readUSB = false;
                    inPaused = true;
                    initPaused = time(NULL);
                    break;
                case 3:
                    inPaused = false;
                    muonRead -> Reset();
                    break;
                case 4:
                    muonRead -> save();
                    break;
                case 5:
                    def_prog_mode();                /* Guardar los modos tty                  */
                    endwin();                       /* Finalizar curnes temporalmente         */

                    muonRead -> Fit();

                    reset_prog_mode();              /* Regresar al modo tty previo            */
                    refresh();  
                    break;
                case 6:
                    readUSB = false;
                    USB.~thread();
                    runProgram = false;
                    break;
                default:
                    break;
            }
    	}
    }
