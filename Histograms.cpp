/**
 *
 * HISTOGRAMS SCRIPT
 * 
 * @author Jaimedgp
 * @version 1.0
 */

#include <cdk.h>
#include "Histograms.h"

Histogram::Histogram (WINDOW* cursesWin, int maxValue, int numColumns, int *value) {

	cdkscreen = initCDKScreen (cursesWin); // init cdk screen in ncurses window
	maxVlue = maxValue; // maximum value for histograms
	numclmns = numColumns; // 

	vlues = value; // values of histograms

	refreshCDKScreen (cdkscreen);
}

Histogram::~Histogram () {

	for (int i = 0; i < sizeof(eachHistograms); ++i) {
		// Destroy each histogram
		destroyCDKHistogram (eachHistograms[i]);
	}

	destroyCDKScreen (cdkscreen);
	endCDK ();
}

void Histogram::buildHistograms(WINDOW* cursesWin, CDK_PARAMS params) {

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

void Histogram::drawIncrement(int i) {

	setCDKHistogramValue (eachHistograms[i], 0, maxVlue, *(events+i));
	refreshCDKScreen (cdkscreen);
}

void Histogram::reDraw() {

	for (int i = 0; i < sizeof(eachHistograms); ++i) {

		setCDKHistogramValue (eachHistograms[i], 0, maxVlue, *(events+i));
	}

	refreshCDKScreen (cdkscreen);
}