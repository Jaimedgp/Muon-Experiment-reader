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

int main (int argc, char **argv) {

    //-----------------------------------
    //         DECLARE VARIABLES  
    //-----------------------------------

    std::string nameOfDevice = "/dev/";

    const char *portname = nameOfDevice.c_str(); // make the pointer of the name of the port a contant
    int fd;

    /** O_RDWR: Open for reading and writing. The result is undefined if this flag is
     * O_NOCTTY: If set and path identifies a terminal device, open() shall not cause the terminal
     *          device to become the controlling terminal for the process. If path does not identify
     *          a terminal device, O_NOCTTY shall be ignored.
     * O_SYNC:  Write I/O operations on the file descriptor shall complete as defined by synchronized
     *          I/O file integrity completion
     */
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC); // open the port

    if (fd < 0) {
        std::cerr << "Error opening " << portname << ": " << std::endl;
        return -1;
    }

    /* simple noncanonical input */
    do {
        char buf[1]; // no idea but maybe the output
        int rdlen; // length of the read value
        rdlen = read(fd, buf, 1); // read the com port

        if (rdlen > 0) {

            std::cout << buf; //print the output in terminal
        }
    } while (1);

}
