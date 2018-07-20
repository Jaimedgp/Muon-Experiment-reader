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

	buildHistograms(cursesWin);

	vlue[numclmns];
	eachHistograms[numclmns];

	for (int i = 0; i < numclmns; ++i ) {
		vlue[i] = 0;
	}

	refreshCDKScreen (cdkscreen);
}

Histograms::~Histograms () {

	for (int i = 0; i < sizeof(eachHistograms); ++i) {
		// Destroy each histogram
		destroyCDKHistogram (eachHistograms[i]);
	}

	destroyCDKScreen (cdkscreen);
	endCDK ();
}

void Histograms::buildHistograms(WINDOW* cursesWin) {

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

		eachHistograms[i] =  newCDKHistogram (cdkscreen,
						    xBorder,  //position of leftup corner X
						    CENTER,                                 // position of left corner Y
						    clmnhght, // height of the column
						    clmnwdth, // width of the column
						    VERTICAL, "", false, false);
	
		if (eachHistograms[i] == 0)	{
			/* Exit CDK. */
			destroyCDKScreen (cdkscreen);
			endCDK ();

			printf ("Cannot make treble histogram. Is the window big enough??\n");
		}

		/* Set the histogram values. */
		setCDKHistogram (eachHistograms[i], vNONE, CENTER, BAR (0, maxVlue, 0));

	    xBorder += clmnwdth + 2;

	}
}

void Histograms::drawIncrement(int i) {

	setCDKHistogramValue (eachHistograms[i], 0, maxVlue, ++vlue[i]);
	refreshCDKScreen (cdkscreen);
}

void Histograms::reDraw() {

	for (int i = 0; i < sizeof(eachHistograms); ++i) {

		setCDKHistogramValue (eachHistograms[i], 0, maxVlue, vlue[i]);
	}

	refreshCDKScreen (cdkscreen);
}