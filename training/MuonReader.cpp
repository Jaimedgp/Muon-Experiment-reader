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

//------------------------------------------
//      DECLARE FUNCTIONS
//------------------------------------------

int hex2Dec (char*);

void save(std::vector<int>);

void clasifiedData(char *, std::vector<int> &, std::vector<time_t> &, time_t &, int &);

//-----------------------------------------------------------
//          
//-----------------------------------------------------------

int main (int argc, char **argv) {

    std::string nameOfDevice = "/dev/ttyUSB0";
    std::vector<int> timer;
    std::vector<time_t> clock;


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
        return -1;
    }

    //bool verdadero = true;
    time_t seconds = time (NULL); // get the seconds since January 1, 1970
    int counter = 0; // number of events with no decay in a second


    /* simple noncanonical input */
    //do {
    for (int i=1; i<200; i++) {
        char buf[3]; // no idea but maybe the output
        int rdlen; // length of the read value

        rdlen = read(fd, buf, sizeof(buf)); // read the com port

        if (rdlen > 0) {

            clasifiedData(buf, timer, clock, seconds, counter);

            rdlen = read(fd, buf, sizeof(buf));

            //verdadero = false;

        }

    } //while (!verdadero);
    
    save(timer);

    return 0;

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

void clasifiedData(char *buf, std::vector<int> &timer, std::vector<time_t> &clock, time_t &seconds, int &counter) {

    
    int number = hex2Dec(buf); // convert hex to dec

    // 40000 means not muon decay
    if (number == 40000) {

        // if events occured in less than a second
        if (seconds == time(NULL)){
            counter++;
        } else {
            timer.push_back(number+counter);
            clock.push_back(seconds);

            seconds = time(NULL);
            counter = 0;
        }
    } else { // Muon decay
        timer.push_back(number);
        clock.push_back(seconds);

        seconds = time(NULL);
    }

}
