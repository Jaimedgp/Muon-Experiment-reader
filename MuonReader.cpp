/**
 *
 * MUONREADER SCRIPT
 * 
 * @author Jaimedgp
 * @version 1.0
 */

#include "MuonReader.h"

MuonReader::MuonReader (WINDOW *muonDcysLy, WINDOW *muonPerMinutLy, WINDOW *showDataLy) {

	muonDcysHis = Histograms(muonDcysLy, 10, 20);

    int numColmns = (COLS-(COLS/15))/4;

    muonPerMinutHis = Histograms(muonPerMinutLy, 200, numColmns);

    dataLy = DataLy(showDataLy);

    nameOfDevice = "/dev/ttyUSB0";

    const char *portname = nameOfDevice.c_str(); // make the pointer of the name of the port a constant
    
    /** O_RDWR:   Open for reading and writing. The result is undefined if this flag is
     *  O_NOCTTY: If set and path identifies a terminal device, open() shall not cause the terminal
     *            device to become the controlling terminal for the process. If path does not identify
     *            a terminal device, O_NOCTTY shall be ignored.
     *  O_SYNC:   Write I/O operations on the file descriptor shall complete as defined by synchronized
     *            I/O file integrity completion
     */
    fileAdress = open(portname, O_RDWR | O_NOCTTY | O_SYNC); // open the port

    if (fileAdress < 0) {
        //ErrorMessage();
    }

    minute = 0;
}

void MuonReader::Reset(){
    elapsed.clear();
    clocks.clear();

    for (int i = 0; i < muonDcysHis.numclmns; ++i) {
        muonDcysHis.vlue[i] = 0;
    }

    for (int i = 0; i < muonPerMinutHis.numclmns; ++i) {
        muonPerMinutHis.vlue[i] = 0;
    }

    muonPerMinutHis.reDraw();
    muonDcysHis.reDraw();
    
    //----------------------------------------------------
    
    dataLy.reset();
    minute = 0;
}

/**
* Save the Data into a file
*
*/
void MuonReader::save() {

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    char Filename[100];
    sprintf(Filename, "Data_%d-%d-%d.txt", day, month, year);

    std::ofstream outputFile(Filename); // open the output File

    for (int i=0; i < elapsed.size(); ++i) {
        outputFile << elapsed[i] << "\t" << clocks[i] << "\n";
    }

    outputFile.close();
}

/**
* convert the hex char to dec integer
*
* char* outputPort: hex char
*/
int MuonReader::hex2Dec (char* outputPort) {

    if (isxdigit(outputPort[0])){
        int number;
        std::stringstream hexadecimal;

        hexadecimal << std::hex << outputPort;
        hexadecimal >> number;

        return number*40;
    } else {
        return -1;
    }
}

char MuonReader::clasifiedData(char *buf) {
   
    int number = hex2Dec(buf); // convert hex to dec

    if (number == -1){
        return 'N';
    }

    // 40000 means not muon decay
    if (number == 40000) {

        // if events occured in less than a second
        if (seconds == time(NULL)){
            counterSec++;
            return 'P';
        } else {

            elapsed.push_back(number+counterSec);
            clocks.push_back(seconds);

            seconds = time(NULL);
            return 'M';
        }
    } else { // Muon decay
        elapsed.push_back(number);
        clocks.push_back(seconds);
        seconds = time(NULL);
        return 'D';
    }

    return 'N';
}

void MuonReader::startReading () {

    counterSec = 0;
    counterMin = 0;
}

void MuonReader::collectData () {

    char buf[3];
    int rdlen;

    rdlen = read(fileAdress, buf, 3);

    if (rdlen > 0 && time(NULL) != timeinit && isdigit(buf[0])) {

        char type = clasifiedData(buf);

        long int elapsetime = seconds - timeinit;
        dataLy.printElapsTime(elapsetime);

        if (type == 'M') {
            ++counterSec;
            counterMin += counterSec;

            dataLy.printNumMuon(counterSec);

            counterSec = 0;
        } else if (type == 'D') {
            dataLy.printMuonDcy();

            int elapse = hex2Dec(buf);
            for (int i = 1; i <=20; ++i) {
                if (elapse < 1000*i) {
                    muonDcysHis.drawIncrement(i-1);
                    break;
                }
            }
        } 

        dataLy.printMuonRate();
        dataLy.printDcyRate();

        if (minute != (elapsetime/60)) {
            muonPerMinutHis.passTime(counterMin);
            minute = elapsetime / 60;
            counterMin = 0;
        }
    }
}

void MuonReader::Fit () {

    TCanvas *win = new TCanvas("win", "win");
    win -> cd();

    int numBins = muonDcysHis.numclmns;

    TH1D *myHisto = new TH1D("MuonDecays", "", numBins, 0, 20);
    myHisto -> SetStats(0);
    myHisto ->GetXaxis()->SetTitle("Muon Decay Time [#mu s]");
    myHisto ->GetYaxis()->SetTitle("Events [Bin]");
    myHisto->SetMarkerStyle(21); 
    
    for (int i=1; i <= numBins; ++i) {
        myHisto -> AddBinContent(i, muonDcysHis.vlue[i-1]);
    }

    TF1 *ex = new TF1("ex", "[0]*exp([1]*x)", 10, 2);
    myHisto -> Fit(ex);


    myHisto -> Draw("E1");

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    char Filename[100];
    sprintf(Filename, "Graph_%d-%d-%d.png", day, month, year);

    win -> SaveAs(Filename);

}
