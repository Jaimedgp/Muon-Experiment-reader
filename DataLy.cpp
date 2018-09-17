#include "DataLy.h"

DataLy::DataLy () {}
DataLy::DataLy (WINDOW *mainWin) {

    time = 0;
    numberMuons = 0;
    muonDcy = 0;


	cursesWin = mainWin;

	int xSize, ySize;
	getmaxyx(cursesWin, ySize, xSize);

    /* X Border */
    xBrdrLabel = xSize/10;
    if (xBrdrLabel < 1) xBrdrLabel = 1;
    if  (xSize < (xBrdrLabel+36)) {
        int error = -1;
    }

    /* Y Border */
    if (ySize < 11) {
        int error = -1;
    }

    yStart = (ySize-9) / 2;

    /* Print Labels */
	mvwprintw(cursesWin, yStart  , xBrdrLabel, "Elapsed Time:");
    mvwprintw(cursesWin, yStart+2, xBrdrLabel, "Number of Muons:");
    mvwprintw(cursesWin, yStart+4, xBrdrLabel, "Muon Rate (per second):");
    mvwprintw(cursesWin, yStart+6, xBrdrLabel, "Muon Decays:");
    mvwprintw(cursesWin, yStart+8, xBrdrLabel, "Decay Rate (per minute):");

    wrefresh(cursesWin);
}

void DataLy::reset() {
    werase(cursesWin);

    numberMuons = 0;
    muonDcy = 0;

    box(cursesWin, 0, 0);

    /* Print Labels */
	mvwprintw(cursesWin, yStart  , xBrdrLabel, "Elapsed Time:");
    mvwprintw(cursesWin, yStart+2, xBrdrLabel, "Number of Muons:");
    mvwprintw(cursesWin, yStart+4, xBrdrLabel, "Muon Rate (per second):");
    mvwprintw(cursesWin, yStart+6, xBrdrLabel, "Muon Decays:");
    mvwprintw(cursesWin, yStart+8, xBrdrLabel, "Decay Rate (per minute):");
    
    wrefresh(cursesWin);
}

void DataLy::printElapsTime(int timer) {

    time = timer;
    int hour = time/3600;
    int restHour = time % 3600;
    minut = restHour / 60;
    int second = restHour % 60;

	mvwprintw(cursesWin, yStart, xBrdrLabel+27, "%02d:%02d:%02d",hour, minut, second);
    wrefresh(cursesWin);
}

void DataLy::printNumMuon(int numMuon) {

    numberMuons += numMuon;
    if (numberMuons < 1000) {
        mvwprintw(cursesWin, yStart+2, xBrdrLabel+27, "%d", numberMuons);
    } else {
        double kiloMuon = (double) numberMuons/1000;
        mvwprintw(cursesWin, yStart+2, xBrdrLabel+27, "%.2f k", kiloMuon);
    }

    wrefresh(cursesWin);
}

void DataLy::printMuonRate() {

    double muonRate = (double) numberMuons / time;

	mvwprintw(cursesWin, yStart+4, xBrdrLabel+27, "%.2f", muonRate);
    wrefresh(cursesWin);
}

void DataLy::printMuonDcy() {
    ++muonDcy;

	mvwprintw(cursesWin, yStart+6, xBrdrLabel+27, "%d", muonDcy);
    wrefresh(cursesWin);
}

void DataLy::printDcyRate() {

    double dcyRate = (double) muonDcy / minut;

	mvwprintw(cursesWin, yStart+8, xBrdrLabel+27, "%.2f", dcyRate);
    wrefresh(cursesWin);
}
