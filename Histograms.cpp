/**
 *
 * HISTOGRAMS SCRIPT
 * 
 * @author Jaimedgp
 * @version 1.0
 */

#include "Histograms.h"

Histograms::Histograms () {
    
}
Histograms::Histograms (WINDOW* cursesWin, int maxValue, int numColumns, char *xName, char *yName) {

    cursWin = cursesWin;
	cdkscreen = initCDKScreen (cursWin); // init cdk screen in ncurses window
	maxVlue = maxValue; // maximum value for histograms
	numclmns = numColumns; // 
    xLabel = xName;
    yLabel = yName;

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

    int ySize, xSize;
    getmaxyx(cursWin, ySize, xSize);


    //----------------------------------
    //         X positions         
    //----------------------------------
    
        xBorder = xSize / 20;

        /* obtain column width */
        if (2*numclmns > (9*xSize/10)) {
            numclmns = (9*xSize/10);
            clmnwdth = 1;
        } else {
            clmnwdth = (9*xSize/10) / numclmns;
        }

        /* if window is not big enough */
        while (xSize < (xBorder + 1 + numclmns*(clmnwdth+2))) {
            if (clmnwdth > 1) {
                --clmnwdth;
            } else if (numclmns > 1) {
                --numclmns;
            } else {
                int err = -1;
            }
        }

        int xPos = xBorder;


    //----------------------------------
    //         Y positions         
    //----------------------------------

        clmnhght = 4*ySize/5;

        yUpPos = ySize/10;

        if (yUpPos < 1) yUpPos = 1;

        while (ySize <= (yUpPos + clmnhght + 4)) {
            if (yUpPos > 1) {
                --yUpPos;
            } else {
                --clmnhght;
            }
        }

        yLwPos = yUpPos + clmnhght + 2;

        /* Print the y-axis */
        mvwprintw(cursWin, yUpPos, xBorder-(3), "%d", maxVlue);
        drawLine (cursWin, xBorder-1, yUpPos+1, xBorder-1, yLwPos, '|');

        /* Print the 0 */
        mvwprintw(cursWin, yLwPos, xBorder-1, "%d", 0);
        drawLine (cursWin, xBorder, yLwPos, xBorder+clmnwdth+2, yLwPos, '-');

    
    //----------------------------------
    //         DRAW HISTOGRAMS     
    //---------------------------------- 

        int i;
        for (i = 0; i < numclmns ; ++i) {

            eachHistograms.push_back (newCDKHistogram (cdkscreen,
                                xPos,  // position of leftup corner X
                                CENTER,
                                clmnhght-1, // height of the column
                                clmnwdth, // width of the column
                                VERTICAL, "", false, false));
        
            if (eachHistograms[i] == 0) {
                /* Exit CDK. */
                destroyCDKScreen (cdkscreen);
                endCDK ();

                int err = -1;
            }

            /* Set the histogram values. */
            setCDKHistogram (eachHistograms[i], vNONE, CENTER, BAR (0, maxVlue, vlue[i]));

            /* print the x axis */
            if (i != 0) {
                char *xVl;
                sprintf(xVl, "%d", i);
                mvwprintw(cursWin, yLwPos, xPos, xVl);
                drawLine (cursWin, xPos+strlen(xVl), yLwPos, xPos+clmnwdth+2, yLwPos, '-');
            }

            xPos += clmnwdth + 2;
        }

        mvwprintw(cursWin, yLwPos, xPos, "%d", i);

    
    //----------------------------------
    //         DRAW LABELS     
    //---------------------------------- 

        if (yLwPos+1 > ySize) {
            --yLwPos;
        }

        xPos = xSize-(xLabel.size()+2);
        mvwprintw(cursWin, yLwPos+1, xPos, "%s", xLabel.c_str());

        int xLabelPos = xBorder / 2;
        int yLabelPos = ((yLwPos-yUpPos) / 2) - (yLabel.size() / 2);
        for (int i=0; i < yLabel.size(); ++i) {
            std::string letter(1, yLabel.at(i));
            mvwprintw(cursWin, yLabelPos+i, xLabelPos, "%s", letter.c_str());
        }

}


void Histograms::drawIncrement(int col) {

	++vlue[col];
    if (vlue[col] >=  maxVlue) {
        maxVlue = vlue[col]+1;
        reDraw();
        mvwprintw(cursWin, yUpPos, xBorder-3, "%d", maxVlue);
    }

	setCDKHistogramValue (eachHistograms[col], 0, maxVlue, vlue[col]);
	drawValues(col);
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
        mvwprintw(cursWin, yUpPos, xBorder-3, "%d", maxVlue);
    }

    reDraw();
}

void Histograms::drawValues(int col) {

    int xPos = xBorder + (1+col)*(clmnwdth+2) - (clmnwdth+2)/2;

    char *mesg[1];

    char number[32];
    char text[32] = "</R>";
    char close[32] = "<!R>";

    sprintf(number, "%d", vlue[col]);
    strcat(text, number);
    strcat(text, close);        

    mesg[0] = text;

    if (vlue[col] > 99) --xPos;

    CDKLABEL *demo = newCDKLabel (cdkscreen, xPos, yUpPos+clmnhght-1, mesg, 1, FALSE, FALSE);

    refreshCDKScreen (cdkscreen);
}
