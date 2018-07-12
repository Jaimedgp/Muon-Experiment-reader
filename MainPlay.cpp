/**
 *  re-write the MounReader script of Pablo Martinez Ruiz del Arbol
 *
 * @author Jaimedgp
 */

#include <iostream>
#include <stdio.h>
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function

#include <vector> // use std::vector
#include <time.h> // get seconds
#include <sstream> // converto hex >> dec

#include <ncurses.h> // Ncurses library
#include <signal.h>

//------------------------------------------
//      DECLARE VARIABLES
//------------------------------------------

WINDOW *graphLayout, *dataLayout, *menuBar;

//------------------------------------------
//      DECLARE FUNCTIONS
//------------------------------------------

void initNcurses ();

void createLayouts(int, int);

bool printGraph(int, int);

void resizeHandler (int);

int hex2Dec (char*);

void save(std::vector<int>);

bool clasifiedData(char *, std::vector<int> &, std::vector<time_t> &, time_t &, int &);

//-----------------------------------------------------------
//          
//-----------------------------------------------------------

int main (int argc, char **argv) {

    std::string nameOfDevice = "/dev/ttyUSB0";
    std::vector<int> timer;
    std::vector<time_t> clock;


    const char *portname = nameOfDevice.c_str(); // make the pointer of the name of the port a constant
    int fd;
    int boolLoop;

    /** O_RDWR: Open for reading and writing. The result is undefined if this flag is
    *  O_NOCTTY: If set and path identifies a terminal device, open() shall not cause the terminal
    *           device to become the controlling terminal for the process. If path does not identify
    *           a terminal device, O_NOCTTY shall be ignored.
    *  O_SYNC:  Write I/O operations on the file descriptor shall complete as defined by synchronized
    *           I/O file integrity completion
    */
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC); // open the port

    if (fd < 0) {
        std::cerr << "Error opening " << portname << ": " << std::endl;
        return -1;
    }

    initNcurses();

    signal(SIGWINCH, resizeHandler);

    //bool verdadero = true;
    time_t seconds = time (NULL); // get the seconds since January 1, 1970
    time_t timeinit = time(NULL);
    int counter = 0; // number of events with no decay in a second
    int numberMuons = 0;


    /* simple noncanonical input */
    do {
    
        char buf[3]; // no idea but maybe the output
        int rdlen; // length of the read value

        rdlen = read(fd, buf, sizeof(buf)); // read the com port

        if (rdlen > 0) {

            if ((time (NULL)) != timeinit) {
             
                boolLoop = clasifiedData(buf, timer, clock, seconds, counter);

                ++numberMuons;
                mvwprintw(dataLayout, 10, 2, "Number of Muons: %d", numberMuons);
                wrefresh(dataLayout);

                int timeSec = (int) clock.size();
                mvwprintw(dataLayout, 12, 2, "time in seconds: %d", timeSec);
                wrefresh(dataLayout);

                double rateMuons = (double) numberMuons/timeSec;
                mvwprintw(dataLayout, 14, 2, "Muons Rate (per second): %.2f", rateMuons);
                wrefresh(dataLayout);

                rdlen = read(fd, buf, sizeof(buf));

            }

        }

    } while (boolLoop);
    
    save(timer);

    endwin();

    return 0;

}

/**
 * Initialize Ncurses window
 *
 */
void initNcurses () {

    initscr();
    cbreak();
    noecho();
    refresh();

    int x, y;
    getmaxyx(stdscr, y, x);
    createLayouts(x, y);
}

/**
 * Draw the Layouts
 *
 */
void createLayouts(int x , int y) {

    graphLayout = newwin(y-1, 2*x/3, 1, x/3);
    box(graphLayout, 0, 0);
    wmove(graphLayout, 2,2);
    wrefresh(graphLayout);

    dataLayout = newwin(y-1, x/3, 1, 0);
    box(dataLayout, 0, 0);
    wrefresh(dataLayout);

}

/**
 * Handler the resize window
 *
 */
void resizeHandler(int sig) {

    endwin();

    initNcurses();

}

/**
 * convert the hex char to dec integer
 *
 * char* outputPort: hex char
 */
int hex2Dec (char* outputPort) {

    int number;
    std::stringstream hexadecimal;

    hexadecimal << std::hex << outputPort;
    hexadecimal >> number;

    return number*40;
}

/**
 * Save the Data into a file
 *
 */
void save(std::vector<int> muonDecay) {

    std::ofstream outputFile("Data.txt"); // open the output File

    for (std::vector<int>::iterator it = muonDecay.begin(); it != muonDecay.end(); ++it) {
        outputFile << *it << "\n";
    }

    outputFile.close();
}

/**
 * Clasified the data depends on the type of event it is
 *
 */

bool clasifiedData(char *buf, std::vector<int> &timer, std::vector<time_t> &clock, time_t &seconds, int &counter) {

    
    int number = hex2Dec(buf); // convert hex to dec
    bool boolean = true;

    // 40000 means not muon decay
    if (number == 40000) {

        // if events occured in less than a second
        if (seconds == time(NULL)){
            counter++;
        } else {

            boolean = printGraph(number+counter, seconds);

            timer.push_back(number+counter);
            clock.push_back(seconds);

            seconds = time(NULL);
            counter = 0;
        }
    } else { // Muon decay
        boolean = printGraph(number, seconds);
        timer.push_back(number);
        clock.push_back(seconds);
    }

    return boolean;
}

/**
 * Print data on screen
 *
 */
bool printGraph(int value, int seconds) {

    int x, y, maxx, maxy;
    getyx(graphLayout, y, x);
    getmaxyx(graphLayout, maxy, maxx);
    
    if (y < maxy-1) {
        mvwprintw(graphLayout, y, x, "%d \t %d" , value, seconds);
        wrefresh(graphLayout);
        wmove(graphLayout, ++y, x);
    } else if (y >= maxy-1) {
        mvwprintw(graphLayout, 2, x+40, "%d \t %d" , value, seconds);
        wrefresh(graphLayout);

        if (x+40 >= maxx) return false;
        wmove(graphLayout, 3, x+40);
    }

    return true;
}
