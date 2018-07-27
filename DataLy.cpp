#include "DataLy.h"

DataLy::DataLy (WINDOW *mainWin) {

    time = 0;
    numberMuons = 0;
    muonDcy = 0;


	cursesWin = mainWin;

	int x;
	getmaxyx(cursesWin, y, x);

	xBrdrLabel = x/10;
	if (xBrdrLabel < 1) xBrdrLabel=1;

	int yBorder = y/8;
	yInterval = (y-yBorder-6)/7;
	if (yInterval < 1) yInterval = 1; 
	y = yInterval+yBorder;

	mvwprintw(cursesWin, y            , xBrdrLabel, "Elapsed Time:");
    mvwprintw(cursesWin, y+yInterval  , xBrdrLabel, "Number of Muons:");
    mvwprintw(cursesWin, y+2*yInterval, xBrdrLabel, "Muon Rate (per second):");
    mvwprintw(cursesWin, y+3*yInterval, xBrdrLabel, "Muon Decays:");
    mvwprintw(cursesWin, y+4*yInterval, xBrdrLabel, "Decay Rate (per minute):");

    wrefresh(cursesWin);
}

void DataLy::printElapsTime(int timer) {

    time = timer;
    int hour = time/3600;
    int restHour = time % 3600;
    int minut = restHour / 60;
    int second = restHour % 60;

	mvwprintw(cursesWin, y, xBrdrLabel+30, "%02d:%02d:%02d",hour, minut, second);
    wrefresh(cursesWin);
}

void DataLy::printNumMuon(int numMuon) {

    numberMuons += numMuon;
	mvwprintw(cursesWin, y+yInterval, xBrdrLabel+30, "%d", numberMuons);
    wrefresh(cursesWin);
}

void DataLy::printMuonRate() {

    double muonRate = (double) numberMuons / time;

	mvwprintw(cursesWin, y+2*yInterval, xBrdrLabel+30, "%.2f", muonRate);
    wrefresh(cursesWin);
}

void DataLy::printMuonDcy() {
    ++muonDcy;

	mvwprintw(cursesWin, y+3*yInterval, xBrdrLabel+30, "%d", muonDcy);
    wrefresh(cursesWin);
}

void DataLy::printDcyRate() {
    double dcyRate = (double) muonDcy / time;

	mvwprintw(cursesWin, y+4*yInterval, xBrdrLabel+30, "%.2f", dcyRate);
    wrefresh(cursesWin);
}
