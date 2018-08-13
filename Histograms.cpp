/**
 *
 * HISTOGRAMS SCRIPT
 * 
 * @author Jaimedgp
 * @version 1.0
 */

#include <cdk.h>
#include "Histograms.h"

Histograms::Histograms () {
    
}
Histograms::Histograms (WINDOW* cursesWin, int maxValue, int numColumns) {

    cursWin = cursesWin;
	cdkscreen = initCDKScreen (cursWin); // init cdk screen in ncurses window
	maxVlue = maxValue; // maximum value for histograms
	numclmns = numColumns; // 

	for (int i = 0; i < numclmns; ++i ) {
		vlue.push_back(0);
	}

	buildHistograms();

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

void Histograms::buildHistograms() {


	getmaxyx(cursWin, y, x);


	xBorder = x/20;

	int Pixl = x-xBorder- 2*numclmns;

	if (numclmns > Pixl) { 
		numclmns = Pixl;
        clmnwdth = 1;
	} else {
        clmnwdth = Pixl/(numclmns);
	}

    clmnhght = 4*(y/5);
    while (clmnhght+3 >= y) {clmnhght -= 1;}

    /* Print the y-axis */
    mvwprintw(cursWin, (y/10)-1, xBorder-(2+1), "%d", maxVlue);
    drawLine (cursWin, xBorder-1, (y/10), xBorder-1, (9*y/10)+1, '|');

    int i;
	for (i = 0; i < numclmns ; ++i) {

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

        /* print the x axis */
        if (i != 0) {
            char *xVl;
            sprintf(xVl, "%d", i);
            mvwprintw(cursWin, (9*y/10)+1, xBorder, xVl);
            drawLine (cursWin, xBorder+strlen(xVl), (9*y/10)+1, xBorder+clmnwdth+2, (9*y/10)+1, '-');
        } else {
            char *xVl;
            mvwprintw(cursWin, (9*y/10)+1, xBorder-1, "%d", 0);
            drawLine (cursWin, xBorder, (9*y/10)+1, xBorder+clmnwdth+2, (9*y/10)+1, '-');
        }

	    xBorder += clmnwdth + 2;

	}

    mvwprintw(cursWin, (9*y/10)+1, xBorder, "%d", i);

}

void Histograms::drawIncrement(int i) {

	++vlue[i];
    if (vlue[i] >=  maxVlue) {
        maxVlue = vlue[i]+1;
        reDraw();
        mvwprintw(cursWin, (y/10)-1, (x/15)-(2+1), "%d", maxVlue);
    }

	setCDKHistogramValue (eachHistograms[i], 0, maxVlue, vlue[i]);
	drawValues(i);
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

    int maxInVector = 0;
    for (int i = 0; i < numclmns; ++i) {
        if (vlue[i] > maxInVector) maxInVector = vlue[i];
    }

    if (maxInVector !=  maxVlue) {
        maxVlue = maxInVector;
        mvwprintw(cursWin, (y/10)-1, (x/15)-(2+1), "%d", maxVlue);
    }

    reDraw();
}

void Histograms::drawValues(int col) {

    int xPos = xBorder - clmnwdth/2;

    xPos -= (numclmns-1-col)*(clmnwdth + 2);

    char *mesg[1];

    char number[32];
    char text[32] = "</R>";
    char close[32] = "<!R>";

    sprintf(number, "%d", vlue[col]);
    strcat(text, number);
    strcat(text, close);        

    mesg[0] = text;

    if (vlue[col] > 99) --xPos;

    CDKLABEL *demo = newCDKLabel (cdkscreen, xPos, clmnhght+4, mesg, 1, FALSE, FALSE);

    refreshCDKScreen (cdkscreen);
}
