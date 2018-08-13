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

		void drawIncrement(int i);

		void buildHistograms();
		void reDraw();
		void passTime (int newTime);
		void drawValues(int col);

        int numclmns;
        int x, y;
   		std::vector<int> vlue;

	private:
        int xBorder, clmnhght, clmnwdth;
   		int maxVlue;

   		std::vector<CDKHISTOGRAM *> eachHistograms;

		CDKSCREEN *cdkscreen;
        WINDOW *cursWin;
};

#endif
