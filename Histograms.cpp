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

	int x, y;

	getmaxyx(cursesWin, y, x);


	xBorder = x/15;

	int Pixl = x-xBorder- 2*numclmns;

	if (numclmns > Pixl) { 
		numclmns = Pixl;
        clmnwdth = 1;
	} else {
        clmnwdth = Pixl/(numclmns);
	}

    clmnhght = 4*(y/5);
    while (clmnhght+3 >= y) clmnhght -= 1;

	for (int i = 0; i < numclmns ; ++i) {

		eachHistograms.push_back (newCDKHistogram (cdkscreen,
						    xBorder,  // position of leftup corner X
						    CENTER,   // position of left corner Y
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
    int xPos = xBorder - clmnwdth/2;

	for (int i = numclmns - 1; i >= 0; --i) {

		setCDKHistogramValue (eachHistograms[i], 0, maxVlue, vlue[i]);

        char         *mesg[1];

        if (vlue[i] > 0) {
            char number[32];
            sprintf(number, "%d", vlue[i]);
            char text[32] = "</R>";
            strcat(text, number);
            char close[32] = "<!R>";
            strcat(text, close);        

            mesg[0] = text;
        } else {
            char text[32] = " ";

            mesg[0] = text;
        }

        CDKLABEL *demo = newCDKLabel (cdkscreen, xPos, clmnhght+4, mesg, 1, FALSE, FALSE);

        xPos -= clmnwdth + 2;
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
