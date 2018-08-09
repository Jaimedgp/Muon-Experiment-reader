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
		Histograms(WINDOW* cursesWin, int maxValue, int numColumns); // Constructor
		
		void destroyHistograms(); // destructor

		void drawIncrement(int i);

		void buildHistograms();
		void reDraw();
		void passTime (int newTime);
		void drawValues();

	private:
        int xBorder, clmnhght, clmnwdth;
   		int maxVlue, numclmns;
   		std::vector<int> vlue;

   		std::vector<CDKHISTOGRAM *> eachHistograms;

		CDKSCREEN *cdkscreen;
        WINDOW *cursWin;
};

#endif
