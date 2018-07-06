/**
 * Play re-writting the MounReader script of Pablo Martinez Ruiz del Arbol
 *
 * @author Jaimedgp
 */

/*
#include <iostream>
#include <stdio.h>
#include <fstream> // write and read package
#include <string.h> // for std::string variables
#include <fcntl.h> // open port function
#include <unistd.h> // read port function
*/

//------------------------------------------------------
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <bitset>
//------------------------------------------------------
int main (int argc, char **argv) {

    //-----------------------------------
    //         DECLARE VARIABLES  
    //-----------------------------------

    std::string nameOfDevice = "/dev/ttyUSB0";
    //std::string nameOfDevice = "pci-0000:00:1d.0-usb-0:1:1.0-port0";
    //std::string nameOfDevice = "/dev/serial/by-path/pci-0000:00:1d.0-usb-0:1:1.0-port0";
    //std::string nameOfDevice = "usb-FTDI_USB__-__Serial-if00-port0";
    //std::string nameOfDevice = "/dev/serial/by-id/usb-FTDI_USB__-__Serial-if00-port0";


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

    bool verdadero = true;
    /* simple noncanonical input */
    do {
        char buf[1]; // no idea but maybe the output
        int rdlen; // length of the read value
        rdlen = read(fd, buf, 1); // read the com port

        if (rdlen > 0) {

            std::cout << buf; //print the output in terminal
            verdadero = false;
        }

    } while (!verdadero);

}
