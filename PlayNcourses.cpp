/**
 * Play with Ncurses showing the Data obtained from USB 
 *
 * @author Jaimedgp
 */

#include <ncurses.h>

int main (int argc, char *argv[]) {

    WINDOW *plotAllData, *plotSelectData;
    
    int ch;

    noecho();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    refresh();

    plotAllData = newwin(LINES-1, 2*COLS/3, 1, COLS/3);
    box(plotAllData, 0, 0);
    wrefresh(plotAllData);

    plotSelectData = newwin(LINES-1, COLS/3, 1, 0);
    box(plotSelectData, 0, 0);
    wrefresh(plotSelectData);


    for (int i = 0; i < 100000; i++) {
        printw("HOLA CHICOS");
    

        if ((ch = getch()) == 'A') {
            break;
        } else {            
            switch (ch) {
                case KEY_RIGHT:
                    wprintw(plotAllData, "1 \n");
                    wrefresh(plotAllData);
                    break;
                case KEY_LEFT:
                    wprintw(plotSelectData, "2 \n");
                    wrefresh(plotSelectData);
                    break;
                default:
                    NULL;
            }

        }
    }

    endwin();
    return 0;

}
