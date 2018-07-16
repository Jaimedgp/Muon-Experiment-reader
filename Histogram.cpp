#include <cdk.h>
#include <iostream>
#include "hstgram.h"

Histogram::Histogram(int argc, char **argv, WINDOW* cursesWin) {

	//cdkscreen = 0;
	//eachHistograms = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cdkscreen = initCDKScreen (cursesWin);

	/* Start CDK Color. */
	//initCDKColor ();

	CDK_PARAMS params;
	boolean Box;

	CDKparseParams (argc, argv, &params, CDK_CLI_PARAMS);
	Box = CDKparamValue (&params, 'N', FALSE);


	int events[10] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int x, y;

	getmaxyx(cursesWin, y, x);

	int xDiv = x/13;
    int xPos = xDiv;
    int yDiv = y/13;

	for (int i = 0; i < 10 ; ++i) {

		eachHistograms[i] =  newCDKHistogram (cdkscreen,
						    CDKparamValue (&params, 'X', xPos), //position of leftup corner X
						    CENTER, // position of left corner Y
						    CDKparamValue (&params, 'H', y - (4*yDiv)), // height of the column
						    CDKparamValue (&params, 'W', xDiv), // width of the column
						    VERTICAL, "",
						    Box,
						    CDKparamValue (&params, 'S', FALSE));
	
		if (eachHistograms[i] == 0)	{
			/* Exit CDK. */
			destroyCDKScreen (cdkscreen);
			endCDK ();

			printf ("Cannot make treble histogram. Is the window big enough??\n");
			//ExitProgram (EXIT_FAILURE);
		}

		/* Set the histogram values. */
		setCDKHistogram (eachHistograms[i], vNONE, CENTER, BAR (0, 10, events[i]));

	    xPos = xPos + 7*xDiv/6;

	}

		refreshCDKScreen (cdkscreen);
		sleep (2);
	
} 

Histogram::~Histogram() {

	for (int i = 0; i < 10 ; ++i) {
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
