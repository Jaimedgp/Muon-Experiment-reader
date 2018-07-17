#include <cdk.h>
#include <iostream>
#include "hstgram.h"

Histogram::Histogram(int argc, char **argv, WINDOW* cursesWin, int maxValue, int numColumns) {

	//cdkscreen = 0;
	//eachHistograms = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cdkscreen = initCDKScreen (cursesWin);
	maxVlue = maxValue;


	/* Start CDK Color. */
	//initCDKColor ();

	CDK_PARAMS params;
	boolean Box;

	CDKparseParams (argc, argv, &params, CDK_CLI_PARAMS);
	Box = CDKparamValue (&params, 'N', FALSE);


	int events[numColumns];

	int x, y;

	getmaxyx(cursesWin, y, x);


	int xBorder = x/15;
	int clmnwdth;

	int Pixl = x-xBorder- 2*numColumns;
	clmnwdth = Pixl/(numColumns);
	
	if (numColumns > Pixl) { 
		numColumns = Pixl;
		clmnwdth = 1;
	} else {
	}

    int clmnhght = 4*(y/5);

	for (int i = 0; i < numColumns ; ++i) {

		eachHistograms[i] =  newCDKHistogram (cdkscreen,
						    CDKparamValue (&params, 'X', xBorder), //position of leftup corner X
						    CENTER, // position of left corner Y
						    CDKparamValue (&params, 'H', clmnhght), // height of the column
						    CDKparamValue (&params, 'W', clmnwdth), // width of the column
						    VERTICAL, "", false, false);
						    //Box,
						    //CDKparamValue (&params, 'S', FALSE));
	
		if (eachHistograms[i] == 0)	{
			/* Exit CDK. */
			destroyCDKScreen (cdkscreen);
			endCDK ();

			printf ("Cannot make treble histogram. Is the window big enough??\n");
			//ExitProgram (EXIT_FAILURE);
		}

		/* Set the histogram values. */
		setCDKHistogram (eachHistograms[i], vNONE, CENTER, BAR (0, maxValue, events[i]));

	    xBorder += clmnwdth + 2;

	}

		refreshCDKScreen (cdkscreen);
		sleep (2);
	
} 

Histogram::~Histogram() {

	for (int i = 0; i < sizeof(eachHistograms) ; ++i) {
		destroyCDKHistogram (eachHistograms[i]);
	}

	destroyCDKScreen (cdkscreen);
	endCDK ();

}

void Histogram::drawIncrement(int i) {

    int randomNumber = rand() % 11;

	setCDKHistogramValue (eachHistograms[i], 0, 10, randomNumber);
	refreshCDKScreen (cdkscreen);
	
}
