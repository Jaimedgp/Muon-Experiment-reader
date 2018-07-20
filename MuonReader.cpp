class MuonReader {

	public:
		bool reading;
		int clock = time(NULL);

		std::vector<int> cronometer;
    	std::vector<time_t> time;

    	int readUSB ();
    	int hex2Dec (char*);
    	int[] clasifiedData (int); 
}

int MuonReader::readUSB () {

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

    char buf[3]; // no idea but maybe the output
    int rdlen; // length of the read value

    rdlen = read(fd, buf, sizeof(buf)); // read the com port
    rdlen = read(fd, buf, sizeof(buf)); // read the com port
    int value = hex2Dec (buf);

    return value
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

int[] clasifiedData (int elapse) {

	int data[2] = {-1, -1};

	// 40000 means not muon decay
    if (number == 40000) {

        // if events occured in less than a second
        if (clock == time(NULL)){
            counter++;
        } else {
            cronometer.push_back(number+counter);
            time.push_back(clock);

            data[1] = counter;
            clock = time(NULL);
            counter = 0;
        }
    } else { // Muon decay
        cronometer.push_back(number);
        time.push_back(clock);

        data[0] = number;
        clock = time(NULL);
    }
}