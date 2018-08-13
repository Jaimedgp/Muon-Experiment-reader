/**
 *
 */

#ifndef Histograms_h
#define Histograms_h
#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), false
#include <cdk.h>
#include <vector>


class Histograms {
	public:
		Histograms(); // Constructor
		Histograms(WINDOW* cursesWin, int maxValue, int numColumns); // Constructor
		
		void destroyHistograms(); // destructor

		void drawIncrement(int col);

		void buildHistograms();
		void reDraw();
		void passTime (int newTime);
		void drawValues(int col);

        int numclmns;
   		std::vector<int> vlue;

	private:
        int xBorder, clmnhght, clmnwdth, maxVlue, yUpPos, yLwPos;

   		std::vector<CDKHISTOGRAM *> eachHistograms;

		CDKSCREEN *cdkscreen;
        WINDOW *cursWin;
};

#endif
