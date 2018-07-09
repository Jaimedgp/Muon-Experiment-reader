/**
 * Play re-writting the MounReader script of Pablo Martinez Ruiz del Arbol
 *
 * @author Jaimedgp
 */

#include <iostream>
#include <stdio.h>
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function

#include <time.h> // get seconds
#include <sstream> // converto hex >> dec
#include <math.h> // to pow 

#include <iomanip>
#include <string>
#include <stdlib.h> // to use atoi (convert char >> int)
#include <typeinfo>

//------------------------------------------
//      DECLARE FUNCTIONS
//------------------------------------------

int hex2Dec (char*);

//-----------------------------------------------------------
//          
//-----------------------------------------------------------

int main (int argc, char **argv) {

    //-----------------------------------
    //         DECLARE VARIABLES  
    //-----------------------------------

    std::string nameOfDevice = "/dev/ttyUSB0";

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
    int counter = 0;
    std::ofstream outputFile("Data.txt");

    /* simple noncanonical input */
    //do {
    for (int i=1; i<200; i++) {
        char buf[3]; // no idea but maybe the output
        int rdlen; // length of the read value

        rdlen = read(fd, buf, sizeof(buf)); // read the com port

        if (rdlen > 0) {
            
            int number = hex2Dec(buf);

            if (number == 40000) {
                if (seconds == time(NULL)){
                    counter++;
                } else {
                    std::cout << number+counter << "\t" << seconds << std::endl;
                    outputFile << number+counter << "\t" << seconds << std::endl;

                    seconds = time(NULL);
                    counter = 0;
                }
            } else {
                std::cout << number << "\t" << seconds << std::endl;
                 outputFile << number << "\t" << seconds << std::endl;

                seconds = time(NULL);
            }

            rdlen = read(fd, buf, sizeof(buf));

            //verdadero = false;

        }

    } //while (!verdadero);
    
    outputFile.close();

    return 0;
}


int hex2Dec (char* outputPort) {

    int number;
    std::stringstream hexadecimal;

    hexadecimal << std::hex << outputPort;
    hexadecimal >> number;

    return number*40;
}
