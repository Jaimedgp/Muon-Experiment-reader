#include <ncurses.h>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function

#include <vector> // use std::vector
#include <time.h> // get seconds
#include <sstream> // converto hex >> dec

#include "Menu.h"
#include "Histograms.h"
#include "DataLy.h"
//#include "DataLy.h"

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

    WINDOW *muonDcysLy, *muonPerMinutLy, *showDataLy;
    bool loop;
    std::vector<int> timer;
    std::vector<time_t> clocks;    

    void createLy (WINDOW *mainWin);

    int hex2Dec (char* outputPort);

    void save(std::vector<int> muonDecay);

    char clasifiedData(char *buf, time_t &seconds, int &counter);

    void closeLoop (WINDOW *stdscr);

    void collectData ();


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------



int main () {

    noecho();
    initscr();          
    cbreak();
    refresh();

    createLy(stdscr);

    std::thread first (closeLoop, stdscr);
   
    first.join();

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
    void save() {

        std::ofstream outputFile("Data.txt"); // open the output File

        for (int i=0; i < timer.size(); ++i) {
            outputFile << timer[i] << "\t" << clocks[i] << "\n";
        }

        outputFile.close();
    }

    /**
     * Clasified the data depends on the type of event it is
     *
     */

    char clasifiedData(char *buf, time_t &seconds, int &counter) {

        
        int number = hex2Dec(buf); // convert hex to dec

        // 40000 means not muon decay
        if (number == 40000) {

            // if events occured in less than a second
            if (seconds == time(NULL)){
                counter++;
            } else {

                timer.push_back(number+counter);
                clocks.push_back(seconds);

                seconds = time(NULL);
                return 'M';
            }
        } else { // Muon decay
            timer.push_back(number);
            clocks.push_back(seconds);
            return 'D';
        }

        return 'N';
    }

    void closeLoop (WINDOW *stdscr) {
        
        Menu mn(stdscr);
        bool runProgram = true;

        do {
            int option = mn.choiseMenu();
            switch(option) {
                case 1:
                    loop = false;
                    {std::thread second (collectData);
                    second.detach();}
                    break;
                case 2:
                    loop = false;
                    break;
                case 4:
                    save();
                    break;
                case 6:
                    loop = false;
                    runProgram = false;
                    break;
                default:
                    break;
            }
        } while(runProgram);
    }


    void collectData () {

        Histograms muonDcysHis = Histograms(muonDcysLy, 10, 20);

        int numColmns = (COLS-(COLS/15))/4;

        Histograms muonPerMinutHis(muonPerMinutLy, 200, numColmns);

        DataLy dataLy(showDataLy);

        //-------------------------------------------
        
        std::string nameOfDevice = "/dev/ttyUSB0";


        time_t seconds = time (NULL);
        
        time_t timeinit = time(NULL);
        int counter = 0;

        const char *portname = nameOfDevice.c_str(); // make the pointer of the name of the port a constant
        int fd;

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
        }
        int counterMin = 0;
        loop = true;


        do {

            char buf[3];
            int rdlen;

            rdlen = read(fd, buf, sizeof(buf));

            if (rdlen > 0 && time(NULL) != timeinit) {

                char type = clasifiedData(buf, seconds, counter);

                int elapsetime = seconds - timeinit;
                dataLy.printElapsTime(elapsetime);

                if (type == 'M') {
                    ++counter;
                    counterMin += counter;
    
                    if ( (elapsetime % 60) == 0) {
                        muonPerMinutHis.passTime(counterMin);
                        counterMin = 0;
                    }

                    dataLy.printNumMuon(counter);
                    dataLy.printMuonRate();

                    counter = 0;
                } else if (type == 'D') {
                    dataLy.printMuonDcy();
                    dataLy.printDcyRate();

                    int elapse = hex2Dec(buf);
                    for (int i = 1; i <=20; ++i) {
                        if (elapse < 600*i) {
                            muonDcysHis.drawIncrement(i);
                            break;
                        }
                    }
                } 


            }
            rdlen = read(fd, buf, sizeof(buf));
        } while (loop);

    }
