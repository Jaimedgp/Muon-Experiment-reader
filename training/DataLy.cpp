#include "DataLy.h"

DataLy::DataLy (WINDOW *cursesWin) {

	cursesWin = cursesWin;

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
}

void DataLy::printElapsTime(int time) {

	mvwprintw(cursesWin, y, xBrdrLabel+30, "%d", time);
}

void DataLy::printNumMuon(int numMuon) {

	mvwprintw(cursesWin, y+yInterval, xBrdrLabel+30, "%d", numMuon);
}

void DataLy::printMuonRate(double muonRate) {

	mvwprintw(cursesWin, y+2*yInterval, xBrdrLabel+30, "%.2f", muonRate);
}

void DataLy::printMuonDcy(int muonDcy) {

	mvwprintw(cursesWin, y+3*yInterval, xBrdrLabel+30, "%d", muonDcy);
}

void DataLy::printDcyRate(double dcyRate) {

	mvwprintw(cursesWin, y+4*yInterval, xBrdrLabel+30, "%.2f", dcyRate);
}