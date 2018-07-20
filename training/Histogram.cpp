#include <cdk.h>
#include <iostream>
#include "Histogram.h"

Histogram::Histogram(int argc, char **argv, WINDOW* cursesWin, int maxValue, int numColumns, int *even) {

	cdkscreen = initCDKScreen (cursesWin);
	maxVlue = maxValue;
	numclmns = numColumns;

	events = even;

	CDK_PARAMS params;

	CDKparseParams (argc, argv, &params, CDK_CLI_PARAMS);

	buildHistograms(cursesWin, params);
	
	refreshCDKScreen (cdkscreen);
	
} 

Histogram::~Histogram() {

	for (int i = 0; i < sizeof(eachHistograms) ; ++i) {
		destroyCDKHistogram (eachHistograms[i]);
	}

	destroyCDKScreen (cdkscreen);
	endCDK ();

}

void Histogram::buildHistograms(WINDOW* cursesWin, CDK_PARAMS params) {

	int events[numclmns];

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
						    CDKparamValue (&params, 'X', xBorder),  //position of leftup corner X
						    CENTER,                                 // position of left corner Y
						    CDKparamValue (&params, 'H', clmnhght), // height of the column
						    CDKparamValue (&params, 'W', clmnwdth), // width of the column
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