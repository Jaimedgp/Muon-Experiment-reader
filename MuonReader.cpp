/**
 *
 *
 */

#include "MuonReader.h"

MuonReader::MuonReader ( std::string Device = "/dev/ttyUSB0") {

	std::string nameOfDevice = Device;
	time_t clock = time(NULL);

	counter = 0;
}

void MuonReader::readLoop () {

	while (reading) {

		int value = readUSB();

		int* pointer = clasifiedData(value);

		if (*(pointer) != -1) {
			//is a muon decay
		}

		if (*(pointer+1) != -1) {
			//its just a muon
		}
	}
}

int MuonReader::readUSB () {


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
        return -1;
    }

    char buf[3]; // no idea but maybe the output
    int rdlen; // length of the read value

    rdlen = read(fd, buf, sizeof(buf)); // read the com port
    rdlen = read(fd, buf, sizeof(buf)); // read the com port
    int value = hex2Dec (buf);

    return value;
}

int* MuonReader::clasifiedData (int elapse) {

	int data[2] = {-1, -1};

	// 40000 means not muon decay
    if (elapse == 40000) {

        // if events occured in less than a second
        if (clock == time(NULL)){
            counter++;
        } else {
            cronometer.push_back(elapse+counter);
            timer.push_back(clock);

            data[1] = counter;
            clock = time(NULL);
            counter = 0;
        }
    } else { // Muon decay
        cronometer.push_back(elapse);
        timer.push_back(clock);

        data[0] = elapse;
        clock = time(NULL);
    }

    int *pointer = data;
    return pointer;
}

/**
 * convert the hex char to dec integer
 *
 * char* outputPort: hex char
 */
int MuonReader::hex2Dec (char* outputPort) {

    int number;
    std::stringstream hexadecimal;

    hexadecimal << std::hex << outputPort;
    hexadecimal >> number;

    return number*40;
}