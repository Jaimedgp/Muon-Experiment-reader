/**
 *
 * HISTOGRAMS SCRIPT
 * 
 * @author Jaimedgp
 * @version 1.0
 */

#include <cdk.h>
#include "Histograms.h"

Histograms::Histograms (WINDOW* cursesWin, int maxValue, int numColumns) {

	cdkscreen = initCDKScreen (cursesWin); // init cdk screen in ncurses window
	maxVlue = maxValue; // maximum value for histograms
	numclmns = numColumns; // 

	//int vlue[numclmns];
	//eachHistograms[numclmns];

	for (int i = 0; i < numclmns; ++i ) {
		vlue.push_back(0);
	}

	buildHistograms(cursesWin);


	refreshCDKScreen (cdkscreen);
} 

void Histograms::destroyHistograms () {

	for (int i = 0; i < numclmns; ++i) {
		// Destroy each histogram
		destroyCDKHistogram (eachHistograms[i]);
	}

	destroyCDKScreen (cdkscreen);
	endCDK ();
}


void Histograms::buildHistograms(WINDOW* cursesWin) {

	/*for (int i = 0; i < sizeof(vlue) ; ++i){
		wprintw(cursesWin, "%d \n", vlue[i]);
	}*/

	int x, y;

	getmaxyx(cursesWin, y, x);


	int xBorder = x/15;
	int clmnwdth;

	int Pixl = x-xBorder- 2*numclmns;

	if (numclmns > Pixl) { 
		numclmns = Pixl;
		clmnwdth = 1;
	} else {
        clmnwdth = Pixl/(numclmns);
	}

    int clmnhght = 4*(y/5);
    while (clmnhght+3 >= y) clmnhght -= 1;

	for (int i = 0; i < numclmns ; ++i) {

		eachHistograms.push_back (newCDKHistogram (cdkscreen,
						    xBorder,  //position of leftup corner X
						    CENTER,                                 // position of left corner Y
						    clmnhght, // height of the column
						    clmnwdth, // width of the column
						    VERTICAL, "", false, false));
	
		if (eachHistograms[i] == 0)	{
			/* Exit CDK. */
			destroyCDKScreen (cdkscreen);
			endCDK ();

			printf ("Cannot make treble histogram. Is the window big enough??\n");
		}


		/* Set the histogram values. */
		setCDKHistogram (eachHistograms[i], vNONE, CENTER, BAR (0, maxVlue, vlue[i]));

		//wprintw(cursesWin, "%d \n", vlue[i]);

	    xBorder += clmnwdth + 2;

	}

}

void Histograms::drawIncrement(int i) {

	++vlue[i];
    if (vlue[i] >=  maxVlue) {
        maxVlue = vlue[i]+1;
        reDraw();
    }

	setCDKHistogramValue (eachHistograms[i], 0, maxVlue, vlue[i]);
	refreshCDKScreen (cdkscreen);
}

void Histograms::reDraw() {

	for (int i = 0; i < numclmns; ++i) {

		setCDKHistogramValue (eachHistograms[i], 0, maxVlue, vlue[i]);
	}

	refreshCDKScreen (cdkscreen);
}

void Histograms::passTime (int newTime) {

	for (int i = numclmns; i >= 0; --i) {

		vlue[i] = vlue[i-1];
	}

	vlue[0] = newTime;

    if (newTime >= maxVlue) maxVlue = newTime+1;

    reDraw();
}
